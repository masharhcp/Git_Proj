

#ifndef LOCK_H_
#define LOCK_H_

#define Lock() { asm pushf; asm cli; }
#define Unlock() asm popf;


#endif
