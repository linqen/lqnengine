//#ifndef IMPORTEXPORT_H
//#define IMPORTEXPORT_H
//#endif
#ifdef LQNENGINE_EXPORTS
#define LQN_API _declspec(dllexport)
#else
#define LQN_API _declspec(dllimport)
#endif
