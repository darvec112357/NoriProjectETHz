git pull
cd build
make -j 4
sbatch --men-per-cpu 16000 --wrap="xvfb-run -a ./nori ../scenes/project/project.xml"