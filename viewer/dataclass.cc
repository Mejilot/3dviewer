#include "dataclass.h"

namespace msp {

SingletonDestroyer::SingletonDestroyer(DataClass *s) { singleton_ = s; }

SingletonDestroyer::~SingletonDestroyer() { delete singleton_; }

void SingletonDestroyer::SetSingleton(DataClass *s) { singleton_ = s; }

}  // namespace msp
