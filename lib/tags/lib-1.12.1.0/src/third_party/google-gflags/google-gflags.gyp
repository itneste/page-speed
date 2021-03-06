# Copyright 2011 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

{
  'variables': {
    'gflags_root': '<(DEPTH)/third_party/google-gflags',
    'gflags_gen_arch_root': '<(gflags_root)/gen/arch/<(OS)/<(target_arch)',
  },
  'targets': [
    {
      'target_name': 'google-gflags',
      'type': '<(library)',
      'include_dirs': [
        '<(gflags_gen_arch_root)/include/private',  # For config.h
        '<(gflags_gen_arch_root)/include',  # For configured files.
        '<(gflags_root)/src',  # For everything else.
      ],
      'defines': [
        # These macros exist so flags and symbols are properly
        # exported when building DLLs. Since we don't build DLLs, we
        # need to disable them.
        'GFLAGS_DLL_DECL=',
        'GFLAGS_DLL_DECLARE_FLAG=',
        'GFLAGS_DLL_DEFINE_FLAG=',
      ],
      'direct_dependent_settings': {
        'include_dirs': [
          '<(gflags_gen_arch_root)/include',  # For configured files.
          '<(gflags_root)/src',  # For everything else.
        ],
        'defines': [
          'GFLAGS_DLL_DECL=',
          'GFLAGS_DLL_DECLARE_FLAG=',
          'GFLAGS_DLL_DEFINE_FLAG=',
        ],
      },
      'sources': [
        'src/gflags.cc',
        'src/gflags_completions.cc',
        'src/gflags_reporting.cc',
      ],
      'conditions': [
        ['OS == "win"', {
          'sources': [
            'src/windows/port.cc',
          ],
        }],
      ],
    },
  ],
}
