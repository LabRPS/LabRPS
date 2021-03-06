/* This file is part of LabRPS.

   Copyright 2016, Arun Narayanankutty <n.arun.lifescience@gmail.com>
   
   LabRPS is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   LabRPS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with LabRPS.  If not, see <http://www.gnu.org/licenses/>.
   
   Description : LabRPS thread handler (handles multi threading)
*/

#ifndef CORE_THREAD_H_
#define CORE_THREAD_H_

#include <QThread>

class Thread : public QThread {
 public:
  Thread(QObject* parent = nullptr)
      : QThread(parent) {}

  void SetIoPriority() {
    // set thread priority here..
    // may be move the prority set to Utilities.cpp
  }
  virtual void run() override;

 private:
  // thread Priory variable here
};

#endif  // CORE_THREAD_H_
