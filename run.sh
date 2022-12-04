git pull
cd build
make -j 4
sbatch -c 16  --wrap="xvfb-run -a ./nori ../scenes/project/project.xml"