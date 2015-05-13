#include "SimulationData.hpp"

QString SimulationData::fileName() const {
    return this->_filename;
}

void SimulationData::setFileName(const QString& fileName) {
    this->_filename = fileName;
    emit fileNameChanged(this->_filename);
}

bool SimulationData::isSaved() const {
    return this->_saved;
}

void SimulationData::setSaved(bool saved) {
    this->_saved = saved;
}
