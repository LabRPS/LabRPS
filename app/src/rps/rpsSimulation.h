#ifndef RPSSIMULATION_H
#define RPSSIMULATION_H

#include <QWidget>
#include "RPSSeaLabsimuData.h"

class RPSSimulation : public QWidget
{
  Q_OBJECT
 
 public:

  RPSSimulation(QWidget *parent = nullptr);
  ~RPSSimulation();
 
};

#endif  // RPSSIMULATION_H