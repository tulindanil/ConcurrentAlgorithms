wget https://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz/download
echo $CPLUS_INCLUDE_PATH
mv download boost.tar.gz
gzip -d boost.tar.gz
tar xvf boost.tar
cd boost_1_60_0/
export CPLUS_INCLUDE_PATH="$(pwd):$CPLUS_INCLUDE_PATH"
echo CPLUS_INCLUDE_PATH