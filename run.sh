git pull
cd build
make -j 4
sbatch --wrap="xvfb-run -a ./nori ../scenes/project/project.xml"