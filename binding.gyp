{
  "targets": [
    {
      "target_name": "btaddon",
      "sources": [
        "addon.cpp",
        "bt_disconnect.cpp"
      ],
      "libraries": [
        "-lBthprops"
      ],
      "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
       "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
    }
  ]
}
