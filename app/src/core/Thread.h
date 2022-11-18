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
