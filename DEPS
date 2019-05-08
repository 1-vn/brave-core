use_relative_paths = True

deps = {
  "vendor/ad-block": "https://github.com/1-vn/ad-block.git@06e74168d5ca27f92c09eff6d15344326e9b6ca1",
  "vendor/autoplay-whitelist": "https://github.com/1-vn/autoplay-whitelist.git@f4430de6a9c33a28ea0c902b0820e65df2eaffa1",
  "vendor/extension-whitelist": "https://github.com/1-vn/extension-whitelist.git@3998119af7052ca04f18d7e65ef8654fc0c675db",
  "vendor/tracking-protection": "https://github.com/1-vn/tracking-protection.git@05404f1d7b99aef56c1c0622df6cfbde3210c21d",
  "vendor/hashset-cpp": "https://github.com/1-vn/hashset-cpp.git@83ec96a95a11684aa02f7b67db54ebf17a759c06",
  "vendor/bloom-filter-cpp": "https://github.com/1-vn/bloom-filter-cpp.git@bae935a734c9a116396f584b0a0226dd40098f7f",
  "vendor/requests": "https://github.com/kennethreitz/requests@e4d59bedfd3c7f4f254f4f5d036587bcd8152458",
  "vendor/boto": "https://github.com/boto/boto@f7574aa6cc2c819430c1f05e9a1a1a666ef8169b",
  "vendor/python-patch": "https://github.com/svn2github/python-patch@a336a458016ced89aba90dfc3f4c8222ae3b1403",
  "vendor/omaha":  "https://github.com/1-vn/omaha.git@3399e8cf515da7c5e6d43bd1cb5415d7f5ee91c4",
  "vendor/sparkle": "https://github.com/1-vn/Sparkle.git@c0759cce415d7c0feae45005c8a013b1898711f0",
  "vendor/bat-native-rapidjson": "https://github.com/1-vn/bat-native-rapidjson.git@86aafe2ef89835ae71c9ed7c2527e3bb3000930e",
  "vendor/bip39wally-core-native": "https://github.com/1-vn/bat-native-bip39wally-core.git@9b119931c702d55be994117eb505d56310720b1d",
  "vendor/bat-native-anonize": "https://github.com/1-vn/bat-native-anonize.git@b8ef1a3f85aec0a0522a9230d59b3958a2150fab",
  "vendor/bat-native-tweetnacl": "https://github.com/1-vn/bat-native-tweetnacl.git@1b4362968c8f22720bfb75af6f506d4ecc0f3116",
  "components/onevn_sync/extension/onevn-sync": "https://github.com/1-vn/sync.git@ac5175401a743e95e6f6cecded9feb736c62a2e0",
  "components/onevn_sync/extension/onevn-crypto": "https://github.com/1-vn/crypto@0e6ebbbfeec1da03c963b97e164776dcc0eff98e",
  "vendor/bat-native-usermodel": "https://github.com/1-vn/bat-native-usermodel.git@b6831d54bbde8e0328b821d5667d0d1c7bb5045b",
  "vendor/challenge_bypass_ristretto_ffi": "https://github.com/1-vn/challenge-bypass-ristretto-ffi.git@5d3b63c7789010914d4a6a3040bf3b2114bdd85c",
}

hooks = [
  {
    'name': 'bootstrap',
    'pattern': '.',
    'action': ['python', 'src/onevn/script/bootstrap.py'],
  },
  {
    # Download rust deps if necessary
    'name': 'download_rust_deps',
    'pattern': '.',
    'action': ['python', 'src/onevn/script/download_rust_deps.py'],
  },
  {
    # Build onevn-sync
    'name': 'build_onevn_sync',
    'pattern': '.',
    'action': ['python', 'src/onevn/script/build-simple-js-bundle.py', '--repo_dir_path', 'src/onevn/components/onevn_sync/extension/onevn-sync'],
  },
  {
    # Build onevn-crypto
    'name': 'build_onevn_crypto',
    'pattern': '.',
    'action': ['python', 'src/onevn/script/build-simple-js-bundle.py', '--repo_dir_path', 'src/onevn/components/onevn_sync/extension/onevn-crypto'],
  }
]
