{
  'targets': [
    {
      'target_name': 'sophia',
      'dependencies': [
        '<(module_root_dir)/deps/sophia/sophia.gyp:sophia',
      ],
      'sources': ['src/sophia.cc', 'src/database_wrap.cc']
    }
  ]
}
