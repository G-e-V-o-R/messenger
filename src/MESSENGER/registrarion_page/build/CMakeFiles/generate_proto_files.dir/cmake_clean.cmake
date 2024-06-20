file(REMOVE_RECURSE
  "CMakeFiles/generate_proto_files"
  "generated/chat.grpc.pb.cc"
  "generated/chat.grpc.pb.h"
  "generated/chat.pb.cc"
  "generated/chat.pb.h"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/generate_proto_files.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
