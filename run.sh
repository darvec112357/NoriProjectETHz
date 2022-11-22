git pull
mkdir build
cd build
cmake ..
make -j 4
sbatch --wrap="xvfb-run -a ./nori /scenes/project/project.xml"
cd ..
git add .
git commit -m "new render image result"
git push 