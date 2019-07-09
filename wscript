from waflib.Tools.compiler_cxx import cxx_compiler
#from scripts.waf import utils

# import subprocess
import os
from waf_au_extensions import utils as au_utility


APPNAME = 'harpocrates' #TODO: REPLACE
VERSION = '1.0.0' #TODO: REPLACE 

cxx_compiler['linux'] = ['clang++']

def options(opt) :
    opt.load('compiler_cxx')

def configure(cnf) :
    cnf.load('compiler_cxx')
    cnf.env.append_value('CXXFLAGS', ['-std=c++17', '-Wall', '-Werror', '-Wextra', '-O3'])
    cnf.env.append_value('LINKFLAGS',
                         ['-pthread'])


def build(bld):
    # REPLACE PROJECT NAME 
    bld(name = 'harpocrates_includes',
        includes='./src',
        export_includes='./src')


    bld.stlib(name = 'harpocrates',
        features = 'cxx cxxstlib',
        target='harpocrates',
        includes='../src',
        source=bld.path.ant_glob('src/harpocrates/**/*.cpp'),
        libs = ['cryptopp'],
        use = ['harpocrates_includes'])    

    bld(name='benchmark',
        features='cxx cxxprogram',
        target='benchmark',
        source='measurements/benchmark.cpp',
	lib = ['cryptopp'],
        use=['harpocrates']
    )
    
    # Build Examples
    # bld.recurse('examples/EXAMPLE_NAME')

    # Build Test
    bld.recurse('test/test_encrypt_decrypt')

def test(t):
    au_utility.run_tests('build/test')

def doc(dc):
    au_utility.generate_documentation()
