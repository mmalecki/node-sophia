{
  'targets': [
    {
      'target_name': 'sophia',
      'dependencies': [
        '<(module_root_dir)/deps/sophia/sophia.gyp:sophia',
      ],
      'include_dirs': [
        "<!(node -p -e \"require('path').relative('.', require('path').dirname(require.resolve('nan')))\")",
      ],
      'sources': [
        'src/sophia.cc',
        'src/database_wrap.cc',
        'src/open_worker.cc',
        'src/set_worker.cc',
        'src/get_worker.cc',
      ]
    }
  ]
}
