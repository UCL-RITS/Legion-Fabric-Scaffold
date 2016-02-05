from fabric.api import *
from mako.template import Template
from contextlib import nested
import mako
import os

env.user='ucgajhe'

env.run_at="/home/"+env.user+"/Scratch/Scaffold/output"
env.deploy_to="/home/"+env.user+"/devel/mpi-scaffold"
env.clone_url="https://github.com/UCL-RITS/MPI-Scaffold.git"
env.hosts=['legion.rc.ucl.ac.uk']

modules = nested(
    prefix('module load cmake'),
    prefix('module swap compilers compilers/gnu/4.9.2'),
    prefix('module load cuda/7.5.18/gnu-4.9.2')
)

@task
def grace():
    env.hosts=['grace.rc.ucl.ac.uk']

@task
def cold(branch='master'):
    run('rm -rf '+env.deploy_to)
    run('mkdir -p '+env.deploy_to)
    run('mkdir -p '+env.run_at)
    with cd(env.deploy_to):
        with modules:
            run('git clone '+env.clone_url)
            run('mkdir MPI-Scaffold/build')
            with cd('MPI-Scaffold/build'):
                run('git checkout '+branch)
                run('cmake .. ')
                run('make')
                run('test/catch')

@task
def warm(branch='master'):
  with cd(env.deploy_to+'/MPI-Scaffold/build'):
    with modules:
        run('git checkout '+branch)
        run('git pull')
        run('cmake ..')
        run('make')
        run('test/catch')

@task
def patch():
  with cd(env.deploy_to+'/MPI-Scaffold'):
    local('git diff > patch.diff')
    put('patch.diff','patch.diff')
    with modules:
        run('git checkout .')
        run('git apply patch.diff')
        with cd('build'):
            run('cmake ..')
            run('make')
            run('test/catch')

@task
def sub(processes=4):
    env.processes=processes
    template_file_path=os.path.join(os.path.dirname(__file__),'legion.sh.mko')
    script_local_path=os.path.join(os.path.dirname(__file__),'legion.sh')
    with open(template_file_path) as template:
        script=Template(template.read()).render(**env)
        with open(script_local_path,'w') as script_file:
            script_file.write(script)
    with cd(env.deploy_to):
        put(script_local_path,'example.sh')
        run('qsub example.sh')

@task
def stat():
    run('qstat')

@task
def fetch():
    with lcd(os.path.join(os.path.dirname(os.path.dirname(__file__)),'results')):
      with cd(env.run_at):
        get('*')
