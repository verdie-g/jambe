{
  "targets": [{
    "target_name": "jambeaddon",
    "cflags": [ "-std=c++17" ],
    "cflags!": [ "-fno-exceptions" ],
    "cflags_cc!": [ "-fno-exceptions", "-std=gnu++1y" ],
    "sources": [
      "cpp/wrapper/router-wrapper.cc",
      "cpp/wrapper/lookup-wrapper.cc",
      "cpp/wrapper/main.cc",
      "cpp/jambe/src/route.cc"
    ],
    "include_dirs": [
      "<!@(node -p \"require('node-addon-api').include\")",
      "cpp/jambe/include",
      "cpp/jambe/src"
    ],
    "libraries": [],
    "dependencies": [
      "<!(node -p \"require('node-addon-api').gyp\")"
    ],
    "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ]
  }]
}
