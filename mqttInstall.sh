export QT_VERSION="6.4.3"

export QT_INSTALL_DIR="${HOME}/Qt"
export CMAKE_BIN_DIR="${QT_INSTALL_DIR}/Tools/CMake/bin"
export QMAKE_BIN_DIR="${QT_INSTALL_DIR}/${QT_VERSION}/gcc_64/bin"
export CMAKE_PREFIX_PATH="${QT_INSTALL_DIR}/${QT_VERSION}/gcc_64/"
export NINJA_DIR="${QT_INSTALL_DIR}/Tools/Ninja"
export PATH="${PATH}:${CMAKE_BIN_DIR}:${QMAKE_BIN_DIR}:${NINJA_DIR}"

cd ~
git clone git://code.qt.io/qt/qtmqtt.git
cd qtmqtt
git checkout ${QT_VERSION}
mkdir build
cd build
${QMAKE_BIN_DIR}/qt-configure-module ..
${CMAKE_BIN_DIR}/cmake --build .
${CMAKE_BIN_DIR}/cmake --install . --verbose
