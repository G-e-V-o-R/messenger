#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "chat.grpc.pb.h"
#include "chat.pb.h"
#include <thread>
#include <pqxx/pqxx>
#include <ctime>
#include <random>

struct User{
	std::string id;
	std::string name;
	std::string session_id;
	std::string net_status;
};

class ChatServiceImpl : public chat::ChatService::Service
{
private:
	
	std::unordered_map<std::string, grpc::ServerReaderWriter<chat::chatMessage, chat::chatMessage>*> clients_;
	std::mutex mutex_;
	pqxx::connection& db_conn_;
	User currentUser_;

private:

	void send_message(chat::chatMessage& message){
		auto it = clients_.find(message.recipient_id());
		if ( it != clients_.end() ){
			std::cout << "ONLINE message sending" << std::endl;; 
			it->second->Write(message);
		}else{
				std::cout << "DB message was sended" << std::endl; 
				pqxx::work txn(db_conn_);
				txn.exec("INSERT INTO messages (from_user, to_user, text) VALUES ('"+message.recipient_id()+"', '"+message.sender_id()+"', '"+message.message_text()+"')");
		}
	}

	void send_message(chat::chatMessage&& message){
		auto it = clients_.find(message.recipient_id());
		if ( it != clients_.end() ){
			std::cout << "ONLINE message sending" << std::endl;; 
			it->second->Write(message);
		}else{
				std::cout << "DB message was sended" << std::endl; 
				pqxx::work txn(db_conn_);
				txn.exec("INSERT INTO messages (from_user, to_user, text) VALUES ('"+message.recipient_id()+"', '"+message.sender_id()+"', '"+message.message_text()+"')");
		}
	}

	int validate_and_get_id(const chat::loginMessage* request){
		pqxx::work txn(db_conn_);
        pqxx::result result = txn.exec("SELECT id FROM users WHERE email = '" + 
										request->username() + "' AND password_hash = '" +
									   	request->password() + "'");
    	txn.commit(); 
        return result[0][0].as<int>();
	}


	void define_user( const std::string& id, const std::string& name,
					  const std::string& session_id, const std::string&& net_status	){
		currentUser_.id = id;
		currentUser_.name = name;
		currentUser_.session_id = session_id;
		currentUser_.net_status = net_status;
	}

	void register_auth_key (){
		pqxx::work txn(db_conn_);
		txn.exec("INSERT INTO sessions (user_id, session_id) VALUES (" +
                txn.quote(currentUser_.id) + ", " + 
                txn.quote(currentUser_.session_id) + ")");
        txn.commit();
	}

	void generate_login_response(chat::loginResponse* response){		
			std::multimap<std::string, std::string> friends = retrieve_messages_with_sender(currentUser_.id);

            response->set_session_id(currentUser_.session_id);
            response->set_id(currentUser_.id);

			for (const auto& message : friends )
			{
				chat::chatMessage* new_message = response->add_messages();
				if (clients_.find(message.first) != clients_.end()) 
					generate_message( new_message, message.first, find_user_name_by_id(message.first),
								   					"online", currentUser_.id, message.second);
				else
					generate_message( new_message, message.first, find_user_name_by_id(message.first),
								   					"offline", currentUser_.id, message.second);
			}
	}

	void handle_messages(grpc::ServerReaderWriter<chat::chatMessage, chat::chatMessage>* stream){
		chat::chatMessage message;
		while(stream->Read(&message)){
			if(message.recipient_id() == "server"){
				std::cout << "Serverakan gorc" << std::endl; 
			}else{
				send_message(message);
			}
		}
	}

	void register_stream( grpc::ServerReaderWriter<chat::chatMessage, chat::chatMessage>* stream ){
		chat::chatMessage message;
		if(stream->Read(&message)){
			currentUser_.name = message.sender_id();
			std::lock_guard<std::mutex> lock(mutex_);
			clients_[currentUser_.name] = stream;			
		}else{
			std::runtime_error("Failed to register client");
		}
	}

	void keep_alive( grpc::ServerReaderWriter<chat::chatMessage, chat::chatMessage>* stream ){
		std::thread([&stream, this](){
			send_message( generate_message("keep alive") );				
		}).detach();
	}

	void generate_message( chat::chatMessage* message, const std::string sender_id, 
										 const std::string sender_name, const std::string&& sender_status,
										 const::std::string recipient_id, const std::string message_text)
	{
		message->set_sender_id( sender_id );
		message->set_sender_name( sender_name );
		message->set_sender_status( sender_status );
		message->set_recipient_id( recipient_id );
		message->set_message_text( message_text );
	}

	chat::chatMessage generate_message( const std::string&& message_text )
	{
		
		chat::chatMessage message;
		message.set_sender_name( "server" );
		message.set_recipient_id( currentUser_.id );
		message.set_message_text( message_text );

		return message;
	}

	std::string gen_session_id(size_t&& length){
	    std::string randomString;
    	const char characters[] = "0123456789"
        	                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            	                  "abcdefghijklmnopqrstuvwxyz";

	    std::default_random_engine engine{std::random_device{}()};
    	std::uniform_int_distribution<int> range(0, sizeof(characters)-2);
	    for (size_t i = 0; i < length; ++i){
    	    randomString += characters[range(engine)];
    	}
    	return randomString;
	}

	std::multimap<std::string, std::string> retrieve_messages_with_sender( const std::string& user_id ) 
	{

		pqxx::work txn(db_conn_);
	    pqxx::result r = txn.exec_params("SELECT from_user, text FROM messages WHERE to_user = $1", user_id);
    	std::multimap<std::string, std::string> messages;
 	    for (auto row : r) {
			if (row["text"].c_str() != "")
        		messages.insert({row["from_user"].as<std::string>(), row["text"].c_str()});
    	}

    	txn.commit();   
    	return messages;
	}

	int findUserIdByEmail(const std::string& email) {
        try {
            pqxx::work txn(db_conn_);
            pqxx::result result = txn.exec("SELECT id FROM users WHERE email = " + txn.quote(email));
            txn.commit();
            if (!result.empty()) {
                return result[0][0].as<int>();
            } else {
                return -1;
            }
        } catch (const std::exception& e) {
            std::cerr << "Database error: " << e.what() << std::endl;
            return -1;
        }
	}

	std::string find_user_name_by_id( const std::string& id ) {
        try {
            pqxx::work txn(db_conn_);
            pqxx::result result = txn.exec("SELECT email FROM users WHERE id = " + txn.quote(id));
            txn.commit();
            if (!result.empty()) {
                return result[0][0].as<std::string>();
            } else {
                return "Deleted user";
            }
        } catch (const std::exception& e) {
            std::cerr << "Database error: " << e.what() << std::endl;
        }
		return "error";
	}
	
public:
	
	ChatServiceImpl( pqxx::connection& conn ): db_conn_(conn){
	    std::cout << "Constructor call(): " << std::endl;
	}
	
	grpc::Status chat( grpc::ServerContext context, grpc::ServerReaderWriter<chat::chatMessage, chat::chatMessage>* stream )
	{
		//pahel useri kapy
		//register_stream( stream );	
		//stexcel keep alive thread
		//keep_alive( stream );
		//mshakel namaknery
		handle_messages( stream );
		//avart return grpc::Status::ok
		return grpc::Status::OK;
	}
//kisat
	grpc::Status registration(grpc::ServerContext* context, const chat::loginMessage* request, chat::registrationResponse* response){
	
		pqxx::work txn(db_conn_);	
        pqxx::result result = txn.exec("SELECT COUNT(*) FROM users WHERE email = '" + 
										request->username() + "'");

 		if(result[0][0].as<int>() == 0){
			txn.exec("INSERT INTO users (email, password_hash) VALUES ('"+request->username()+"', '"+request->password()+"')");
        	response->set_text("Successfully registered user");
		}else{
			response->set_text("try another username");
		}

		txn.commit();
        std::cout << "Inserted email and password into the database" << std::endl;
        
		return grpc::Status::OK;	
	}

	grpc::Status log_in(grpc::ServerContext* context, const chat::loginMessage* request, chat::loginResponse* response) 
	
	{
		try {
			int id = validate_and_get_id(request);
			if (id > 0) {
				define_user(std::to_string(id), request->username(),  gen_session_id(32), "online");
				register_auth_key();
				generate_login_response(response);
	        } else {
    	        response->set_session_id("invalid_credentials");
        	}
	        return grpc::Status::OK;
    
		} catch (const std::exception& e) {
        	std::cerr << e.what();
        	response->set_session_id("error");
        	return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
    	}
	}
};


void run_server(const std::string& db_conn_str ){
	try{
//	/*	pqxx::connection conn( db_conn_str);
		std::string server_address("127.0.0.1:8080");
//		ChatServiceImpl service(conn);
		
		grpc::ServerBuilder builder;
		builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	/*	builder.RegisterService(&service);
		std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
		std::cout << "Server listening port 8080" << std::endl;
	    server->Wait();	
*/
	} catch ( const std::exception& e ){
		std::cerr << "Error " << std::endl;
	}
}


int main(){
	std::string db_conn_str ="dbname=messenger user=postgres password=postgres hostaddr=127.0.0.1 port=5432"; 
	//run_server(db_conn_str);
	std::cout << "stacvma";
	return 0;
}
