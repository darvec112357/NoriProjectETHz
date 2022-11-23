git pull
cd build
make -j 4
sbatch -c 128  --wrap="xvfb-run -a ./nori ../scenes/project/project.xml"