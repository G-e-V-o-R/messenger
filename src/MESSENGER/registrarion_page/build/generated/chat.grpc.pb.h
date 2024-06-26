// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: chat.proto
#ifndef GRPC_chat_2eproto__INCLUDED
#define GRPC_chat_2eproto__INCLUDED

#include "chat.pb.h"

#include <functional>
#include <grpc/impl/codegen/port_platform.h>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace chat {

class ChatService final {
 public:
  static constexpr char const* service_full_name() {
    return "chat.ChatService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::chat::chatMessage, ::chat::chatMessage>> chat(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::chat::chatMessage, ::chat::chatMessage>>(chatRaw(context));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::chat::chatMessage, ::chat::chatMessage>> Asyncchat(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::chat::chatMessage, ::chat::chatMessage>>(AsyncchatRaw(context, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::chat::chatMessage, ::chat::chatMessage>> PrepareAsyncchat(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::chat::chatMessage, ::chat::chatMessage>>(PrepareAsyncchatRaw(context, cq));
    }
    virtual ::grpc::Status log_in(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::chat::loginResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chat::loginResponse>> Asynclog_in(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chat::loginResponse>>(Asynclog_inRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chat::loginResponse>> PrepareAsynclog_in(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chat::loginResponse>>(PrepareAsynclog_inRaw(context, request, cq));
    }
    virtual ::grpc::Status registration(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::chat::registrationResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chat::registrationResponse>> Asyncregistration(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chat::registrationResponse>>(AsyncregistrationRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chat::registrationResponse>> PrepareAsyncregistration(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chat::registrationResponse>>(PrepareAsyncregistrationRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void chat(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::chat::chatMessage,::chat::chatMessage>* reactor) = 0;
      #else
      virtual void chat(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::chat::chatMessage,::chat::chatMessage>* reactor) = 0;
      #endif
      virtual void log_in(::grpc::ClientContext* context, const ::chat::loginMessage* request, ::chat::loginResponse* response, std::function<void(::grpc::Status)>) = 0;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void log_in(::grpc::ClientContext* context, const ::chat::loginMessage* request, ::chat::loginResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void log_in(::grpc::ClientContext* context, const ::chat::loginMessage* request, ::chat::loginResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
      virtual void registration(::grpc::ClientContext* context, const ::chat::loginMessage* request, ::chat::registrationResponse* response, std::function<void(::grpc::Status)>) = 0;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void registration(::grpc::ClientContext* context, const ::chat::loginMessage* request, ::chat::registrationResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void registration(::grpc::ClientContext* context, const ::chat::loginMessage* request, ::chat::registrationResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
    };
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    typedef class experimental_async_interface async_interface;
    #endif
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    async_interface* async() { return experimental_async(); }
    #endif
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientReaderWriterInterface< ::chat::chatMessage, ::chat::chatMessage>* chatRaw(::grpc::ClientContext* context) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::chat::chatMessage, ::chat::chatMessage>* AsyncchatRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::chat::chatMessage, ::chat::chatMessage>* PrepareAsyncchatRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::chat::loginResponse>* Asynclog_inRaw(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::chat::loginResponse>* PrepareAsynclog_inRaw(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::chat::registrationResponse>* AsyncregistrationRaw(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::chat::registrationResponse>* PrepareAsyncregistrationRaw(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    std::unique_ptr< ::grpc::ClientReaderWriter< ::chat::chatMessage, ::chat::chatMessage>> chat(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriter< ::chat::chatMessage, ::chat::chatMessage>>(chatRaw(context));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::chat::chatMessage, ::chat::chatMessage>> Asyncchat(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::chat::chatMessage, ::chat::chatMessage>>(AsyncchatRaw(context, cq, tag));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::chat::chatMessage, ::chat::chatMessage>> PrepareAsyncchat(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::chat::chatMessage, ::chat::chatMessage>>(PrepareAsyncchatRaw(context, cq));
    }
    ::grpc::Status log_in(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::chat::loginResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chat::loginResponse>> Asynclog_in(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chat::loginResponse>>(Asynclog_inRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chat::loginResponse>> PrepareAsynclog_in(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chat::loginResponse>>(PrepareAsynclog_inRaw(context, request, cq));
    }
    ::grpc::Status registration(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::chat::registrationResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chat::registrationResponse>> Asyncregistration(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chat::registrationResponse>>(AsyncregistrationRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chat::registrationResponse>> PrepareAsyncregistration(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chat::registrationResponse>>(PrepareAsyncregistrationRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void chat(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::chat::chatMessage,::chat::chatMessage>* reactor) override;
      #else
      void chat(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::chat::chatMessage,::chat::chatMessage>* reactor) override;
      #endif
      void log_in(::grpc::ClientContext* context, const ::chat::loginMessage* request, ::chat::loginResponse* response, std::function<void(::grpc::Status)>) override;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void log_in(::grpc::ClientContext* context, const ::chat::loginMessage* request, ::chat::loginResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void log_in(::grpc::ClientContext* context, const ::chat::loginMessage* request, ::chat::loginResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
      void registration(::grpc::ClientContext* context, const ::chat::loginMessage* request, ::chat::registrationResponse* response, std::function<void(::grpc::Status)>) override;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void registration(::grpc::ClientContext* context, const ::chat::loginMessage* request, ::chat::registrationResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void registration(::grpc::ClientContext* context, const ::chat::loginMessage* request, ::chat::registrationResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientReaderWriter< ::chat::chatMessage, ::chat::chatMessage>* chatRaw(::grpc::ClientContext* context) override;
    ::grpc::ClientAsyncReaderWriter< ::chat::chatMessage, ::chat::chatMessage>* AsyncchatRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReaderWriter< ::chat::chatMessage, ::chat::chatMessage>* PrepareAsyncchatRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::chat::loginResponse>* Asynclog_inRaw(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::chat::loginResponse>* PrepareAsynclog_inRaw(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::chat::registrationResponse>* AsyncregistrationRaw(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::chat::registrationResponse>* PrepareAsyncregistrationRaw(::grpc::ClientContext* context, const ::chat::loginMessage& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_chat_;
    const ::grpc::internal::RpcMethod rpcmethod_log_in_;
    const ::grpc::internal::RpcMethod rpcmethod_registration_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status chat(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::chat::chatMessage, ::chat::chatMessage>* stream);
    virtual ::grpc::Status log_in(::grpc::ServerContext* context, const ::chat::loginMessage* request, ::chat::loginResponse* response);
    virtual ::grpc::Status registration(::grpc::ServerContext* context, const ::chat::loginMessage* request, ::chat::registrationResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_chat : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_chat() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_chat() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status chat(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::chat::chatMessage, ::chat::chatMessage>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestchat(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::chat::chatMessage, ::chat::chatMessage>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(0, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_log_in : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_log_in() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_log_in() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status log_in(::grpc::ServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::loginResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestlog_in(::grpc::ServerContext* context, ::chat::loginMessage* request, ::grpc::ServerAsyncResponseWriter< ::chat::loginResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_registration : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_registration() {
      ::grpc::Service::MarkMethodAsync(2);
    }
    ~WithAsyncMethod_registration() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status registration(::grpc::ServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::registrationResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestregistration(::grpc::ServerContext* context, ::chat::loginMessage* request, ::grpc::ServerAsyncResponseWriter< ::chat::registrationResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_chat<WithAsyncMethod_log_in<WithAsyncMethod_registration<Service > > > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_chat : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_chat() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(0,
          new ::grpc::internal::CallbackBidiHandler< ::chat::chatMessage, ::chat::chatMessage>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context) { return this->chat(context); }));
    }
    ~ExperimentalWithCallbackMethod_chat() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status chat(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::chat::chatMessage, ::chat::chatMessage>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerBidiReactor< ::chat::chatMessage, ::chat::chatMessage>* chat(
      ::grpc::CallbackServerContext* /*context*/)
    #else
    virtual ::grpc::experimental::ServerBidiReactor< ::chat::chatMessage, ::chat::chatMessage>* chat(
      ::grpc::experimental::CallbackServerContext* /*context*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_log_in : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_log_in() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::chat::loginMessage, ::chat::loginResponse>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::chat::loginMessage* request, ::chat::loginResponse* response) { return this->log_in(context, request, response); }));}
    void SetMessageAllocatorFor_log_in(
        ::grpc::experimental::MessageAllocator< ::chat::loginMessage, ::chat::loginResponse>* allocator) {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
    #else
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::experimental().GetHandler(1);
    #endif
      static_cast<::grpc::internal::CallbackUnaryHandler< ::chat::loginMessage, ::chat::loginResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_log_in() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status log_in(::grpc::ServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::loginResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* log_in(
      ::grpc::CallbackServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::loginResponse* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* log_in(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::loginResponse* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_registration : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_registration() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(2,
          new ::grpc::internal::CallbackUnaryHandler< ::chat::loginMessage, ::chat::registrationResponse>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::chat::loginMessage* request, ::chat::registrationResponse* response) { return this->registration(context, request, response); }));}
    void SetMessageAllocatorFor_registration(
        ::grpc::experimental::MessageAllocator< ::chat::loginMessage, ::chat::registrationResponse>* allocator) {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(2);
    #else
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::experimental().GetHandler(2);
    #endif
      static_cast<::grpc::internal::CallbackUnaryHandler< ::chat::loginMessage, ::chat::registrationResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_registration() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status registration(::grpc::ServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::registrationResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* registration(
      ::grpc::CallbackServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::registrationResponse* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* registration(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::registrationResponse* /*response*/)
    #endif
      { return nullptr; }
  };
  #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
  typedef ExperimentalWithCallbackMethod_chat<ExperimentalWithCallbackMethod_log_in<ExperimentalWithCallbackMethod_registration<Service > > > CallbackService;
  #endif

  typedef ExperimentalWithCallbackMethod_chat<ExperimentalWithCallbackMethod_log_in<ExperimentalWithCallbackMethod_registration<Service > > > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_chat : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_chat() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_chat() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status chat(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::chat::chatMessage, ::chat::chatMessage>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_log_in : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_log_in() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_log_in() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status log_in(::grpc::ServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::loginResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_registration : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_registration() {
      ::grpc::Service::MarkMethodGeneric(2);
    }
    ~WithGenericMethod_registration() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status registration(::grpc::ServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::registrationResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_chat : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_chat() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_chat() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status chat(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::chat::chatMessage, ::chat::chatMessage>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestchat(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(0, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_log_in : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_log_in() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_log_in() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status log_in(::grpc::ServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::loginResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestlog_in(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_registration : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_registration() {
      ::grpc::Service::MarkMethodRaw(2);
    }
    ~WithRawMethod_registration() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status registration(::grpc::ServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::registrationResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestregistration(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_chat : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_chat() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackBidiHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context) { return this->chat(context); }));
    }
    ~ExperimentalWithRawCallbackMethod_chat() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status chat(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::chat::chatMessage, ::chat::chatMessage>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerBidiReactor< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* chat(
      ::grpc::CallbackServerContext* /*context*/)
    #else
    virtual ::grpc::experimental::ServerBidiReactor< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* chat(
      ::grpc::experimental::CallbackServerContext* /*context*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_log_in : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_log_in() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->log_in(context, request, response); }));
    }
    ~ExperimentalWithRawCallbackMethod_log_in() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status log_in(::grpc::ServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::loginResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* log_in(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* log_in(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_registration : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_registration() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(2,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->registration(context, request, response); }));
    }
    ~ExperimentalWithRawCallbackMethod_registration() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status registration(::grpc::ServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::registrationResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* registration(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* registration(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_log_in : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_log_in() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler<
          ::chat::loginMessage, ::chat::loginResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::chat::loginMessage, ::chat::loginResponse>* streamer) {
                       return this->Streamedlog_in(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_log_in() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status log_in(::grpc::ServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::loginResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status Streamedlog_in(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::chat::loginMessage,::chat::loginResponse>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_registration : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_registration() {
      ::grpc::Service::MarkMethodStreamed(2,
        new ::grpc::internal::StreamedUnaryHandler<
          ::chat::loginMessage, ::chat::registrationResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::chat::loginMessage, ::chat::registrationResponse>* streamer) {
                       return this->Streamedregistration(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_registration() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status registration(::grpc::ServerContext* /*context*/, const ::chat::loginMessage* /*request*/, ::chat::registrationResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status Streamedregistration(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::chat::loginMessage,::chat::registrationResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_log_in<WithStreamedUnaryMethod_registration<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_log_in<WithStreamedUnaryMethod_registration<Service > > StreamedService;
};

}  // namespace chat


#endif  // GRPC_chat_2eproto__INCLUDED
