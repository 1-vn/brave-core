use_relative_paths = True

deps = {
  "vendor/ad-block": "https://github.com/brave/ad-block.git@d549e9afb5ec6ce01c6be3193b631db8bee53fe5",
  "vendor/tracking-protection": "https://github.com/brave/tracking-protection.git@0931529eba33109c6b3946a83295577fea540045",
  "vendor/hashset-cpp": "https://github.com/bbondy/hashset-cpp.git@f427324d667d7188a9e0975cca7f3a8c06226b4d",
  "vendor/bloom-filter-cpp": "https://github.com/bbondy/bloom-filter-cpp.git@6faa14ececa33badad149c40f94ff9867159681c",
  "vendor/brave-extension": "https://github.com/brave/brave-extension.git@a1e99dabc60f4055ae095ca8e6cc86f719c9f429",
  "vendor/requests": "https://github.com/kennethreitz/requests@e4d59bedfd3c7f4f254f4f5d036587bcd8152458",
  "vendor/boto": "https://github.com/boto/boto@f7574aa6cc2c819430c1f05e9a1a1a666ef8169b",
  "vendor/python-patch": "https://github.com/svn2github/python-patch@a336a458016ced89aba90dfc3f4c8222ae3b1403",
}

hooks = [
  {
    'name': 'bootstrap',
    'pattern': '.',
    'action': ['python', 'src/brave/script/bootstrap.py'],
  },
  {
    # Apply patches to chromium src
    'name': 'apply_patches',
    'pattern': '.',
    'action': ['python', 'src/brave/script/apply-patches.py'],
  },
  {
    # Run npm install for brave-extension
    'name': 'init',
    'pattern': '.',
    'action': ['python', 'src/brave/script/init-brave-extension.py'],
  }
]
