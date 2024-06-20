websocat ws://localhost:8080 -H "Session-ID: M3bMiycc2ha5sPctuohN24z7Wwaghghi"
websocat ws://localhost:8080 -H "Session-ID: ooWkbKFDSxLCBK6J2XPOQKdjyZjvH98P"

curl -X POST http://localhost:8080/registration \
     -H "Content-Type: application/json" \
     -d '{"email":"test@gmail.com", "password":"password"}'

curl -X POST http://localhost:8080/login \
    -H "Content-Type: application/json" \
    -d '{"email":"user@example.com", "password":"password123"}'

curl -X POST http://localhost:8080/logout \
     -H "Session-ID: 8rzu2vtgiJbxeSIg8f9AYGPs0lBSs6er"