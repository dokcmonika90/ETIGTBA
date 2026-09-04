#include <jni.h>
#include <cstdint>
#include <vector>
#include <string>

namespace nes {
struct CPU { uint16_t pc=0; uint8_t a=0,x=0,y=0,p=0x24,sp=0xfd; std::vector<uint8_t> ram{0x8000}; };
static CPU cpu;

static void step(uint8_t op) {
    switch(op) {
        case 0xEA: cpu.pc++; break;                 // NOP
        case 0xA9: cpu.a=cpu.ram[(cpu.pc+1)&0x7fff]; cpu.pc+=2; break; // LDA #imm
        case 0xA2: cpu.x=cpu.ram[(cpu.pc+1)&0x7fff]; cpu.pc+=2; break; // LDX #imm
        case 0xA0: cpu.y=cpu.ram[(cpu.pc+1)&0x7fff]; cpu.pc+=2; break; // LDY #imm
        case 0xAA: cpu.x=cpu.a; cpu.pc++; break;    // TAX
        case 0x8A: cpu.a=cpu.x; cpu.pc++; break;    // TXA
        case 0xE8: cpu.x++; cpu.pc++; break;        // INX
        case 0xCA: cpu.x--; cpu.pc++; break;        // DEX
        default: cpu.pc++; break;                  // safe fallback while ISA grows
    }
}
}

extern "C" JNIEXPORT jstring JNICALL Java_com_eigtba_recompiler_MainActivity_nativeVersion(JNIEnv* env, jobject) {
    return env->NewStringUTF("NES ARM64 Recompiler core 0.1");
}
extern "C" JNIEXPORT void JNICALL Java_com_eigtba_recompiler_MainActivity_nativeReset(JNIEnv*, jobject) { nes::cpu = nes::CPU{}; }
extern "C" JNIEXPORT jboolean JNICALL Java_com_eigtba_recompiler_MainActivity_nativeLoad(JNIEnv*, jobject, jbyteArray data) { return data != nullptr ? JNI_TRUE : JNI_FALSE; }
