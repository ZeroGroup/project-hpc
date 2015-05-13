#ifndef SIMULATION_DATA_HPP_
#define SIMULATION_DATA_HPP_

#include <QObject>

class SimulationData : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(bool saved READ isSaved WRITE setSaved NOTIFY savedChanged)
public:
    QString fileName() const ;
    void setFileName(const QString& fileName);

    bool isSaved() const ;
    void setSaved(bool saved);

signals:
    void fileNameChanged(QString fileName);
    void savedChanged(bool saved);

private:
    QString _filename;
    bool _saved;
};

#endif  // SIMULATION_DATA_HPP_
