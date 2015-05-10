#include <hpc/sensors/SensorNetwork.hpp>

#include <hpc/sensors/Network.hpp>
#include <hpc/sensors/World.hpp>

SensorNetwork::SensorNetwork(int n) {
    _network_data = n;
    network_init();
}

SensorNetwork::~SensorNetwork() {
    network_destroy();
}

void SensorNetwork::start() {
    network_start();
}

void SensorNetwork::stop() {
    network_stop();
}

void SensorNetwork::push() {
    // create WorldInfoDataStream
    WorldUpdateDataStream datastream;
    // fill update info
    // ...
    // push data to DEVICE
    network_push(datastream);
}

void SensorNetwork::pull() {
    // pull messages from DEVICE
    std::queue<Message> messages = network_pull();

    // process messages
    // ...
}

#include <fstream>

#include <boost/archive/xml_iarchive.hpp>

void SensorNetwork::load(const std::string& filename) {
    // open the archive
    std::ifstream ifs(filename);

    if (ifs.good()){
        boost::archive::xml_iarchive ia(ifs);

        // restore the network from the archive
        ia >> boost::serialization::make_nvp("SensorNetwork", *this);
    }
}

#include <boost/archive/xml_oarchive.hpp>

void SensorNetwork::save(const std::string& filename) {
    // make an archive
    std::ofstream ofs(filename);

    if (ofs.good()){
        boost::archive::xml_oarchive oa(ofs);

        oa << boost::serialization::make_nvp("SensorNetwork", *this);
    }
}
