using System;
using System.Collections.Generic;
using System.Text;

namespace SlimGen
{
    [Flags]
    public enum CpuFeatures : long
    {
        None = 0,
        FPUOnChip = (1 << 0),
        VirtualModeEnhancements = (1 << 1),
        DebuggingExtensions = (1 << 2),
        PageSizeExtensions = (1 << 3),
        TimeStampCounter = (1 << 4),
        CPLQualifiedDebugStore = (1 << 5),
        PhysicalAddressExtensions = (1 << 6),
        MachineCheckException = (1 << 7),
        VirtualMachineExtensions = (1 << 8),
        APICOnChip = (1 << 9),
        SaferModeExtensions = (1 << 10),
        EnhancedIntelSpeedStepTechnology = (1 << 11),
        MemoryTypeRangeRegisters = (1 << 12),
        PTEGlobalBit = (1 << 13),
        MachineCheckArchitecture = (1 << 14),
        ThermalMonitor2 = (1 << 15),
        PageAttributeTable = (1 << 16),
        PageSizeExtension36Bit = (1 << 17),
        ProcessorSerialNumber = (1 << 18),
        L1ContextID = (1 << 19),
        XtprUpdateControl = (1 << 20),
        DebugStore = (1 << 21),
        ThermalMonitorAndClockControl = (1 << 22),
        PerfDebugCapabilities = (1 << 23),
        DirectCacheAccess = (1 << 24),
        X2APIC = (1 << 25),
        LAHF_SAHFAvailableIn64Bit = (1 << 26),
        SelfSnoop = (1 << 27),
        Multithreading = (1 << 28),
        ThermalMonitor = (1 << 29),
        CoreMultiprocessingLegacyMode = (1 << 30),
        PendingBreakEnable = (1 << 31),
        SecureVirtualMachine = (1L << 32),
        ExtendedAPICRegisterSpace = (1L << 33),
        MisalignedSSESupport = (1L << 34),
        SyscallAvailableIn64Bit = (1L << 35),
        ExecuteDisableBitAvailable = (1L << 36),
        PageSupport1GB = (1L << 37),
        Supports64Bit = (1L << 38)
    }

    [Flags]
    public enum ExtraInstructions
    {
        None = 0,
        MONITOR = (1 << 0),
        MWAIT = (1 << 1),
        CMPXCHG16B = (1 << 2),
        MOVBE = (1 << 3),
        POPCNT = (1 << 4),
        XSAVE = (1 << 5),
        OSXSAVE = (1 << 6),
        RDMSR = (1 << 7),
        WRMSR = (1 << 8),
        CMPXCHG8B = (1 << 9),
        SYSENTER = (1 << 10),
        SYSEXIT = (1 << 11),
        CMOV = (1 << 12),
        CFLUSH = (1 << 13),
        FXSAVE = (1 << 14),
        FXRSTOR = (1 << 15),
        AltMovCr8 = (1 << 16),
        LZCNT = (1 << 17),
        PREFETCH = (1 << 18),
        SKINIT = (1 << 19),
        DEV = (1 << 20),
        FFXSR = (1 << 21),
        RDTCSP = (1 << 22)
    }

    [Flags]
    public enum InstructionSets
    {
        None = 0,
        MMX = (1 << 0),
        SSE = (1 << 1),
        SSE2 = (1 << 2),
        SSE3 = (1 << 3),
        SSSE3 = (1 << 4),
        SSE41 = (1 << 5),
        SSE42 = (1 << 6),
        SSE4A = (1 << 7),
        AVX = (1 << 8),
        FMA = (1 << 9),
        AES = (1 << 10),
        MMXEx = (1 << 11),
        Amd3DNow = (1 << 12),
        Amd3DNowEx = (1 << 13)
    }

    public static class CpuInformation
    {
        public static readonly string Manufacturer = "";
        public static readonly string Brand = "";
        public static readonly int SteppingID;
        public static readonly int Model;
        public static readonly int Family;
        public static readonly int ProcessorType;
        public static readonly int ExtendedModel;
        public static readonly int ExtendedFamily;
        public static readonly int BrandIndex;
        public static readonly int APICPhysicalID;
        public static readonly int CFLUSHCacheLineSize;
        public static readonly int LogicalProcessorCount;
        public static readonly CpuFeatures Features;
        public static readonly ExtraInstructions ExtraInstructions;
        public static readonly InstructionSets InstructionSets;

        static CpuInformation()
        {
            CPUInfo info = NativeMethods.cpuid(0);
            Manufacturer = Encoding.ASCII.GetString(BitConverter.GetBytes(info[1])) +
                Encoding.ASCII.GetString(BitConverter.GetBytes(info[3])) + Encoding.ASCII.GetString(BitConverter.GetBytes(info[2]));

            info = NativeMethods.cpuid(1);
            SteppingID = info[0] & 0xf;
            Model = (info[0] >> 4) & 0xf;
            Family = (info[0] >> 8) & 0xf;
            ProcessorType = (info[0] >> 12) & 0x3;
            ExtendedModel = (info[0] >> 16) & 0xf;
            ExtendedFamily = (info[0] >> 20) & 0xff;
            BrandIndex = info[1] & 0xff;
            CFLUSHCacheLineSize = ((info[1] >> 8) & 0xff) * 8;
            LogicalProcessorCount = ((info[1] >> 16) & 0xff);
            APICPhysicalID = (info[1] >> 24) & 0xff;
            Features = CpuFeatures.None;
            ExtraInstructions = ExtraInstructions.None;
            InstructionSets = InstructionSets.None;

            if ((info[2] & 0x1) != 0)
                InstructionSets |= InstructionSets.SSE3;
            if ((info[2] & 0x8) != 0)
                ExtraInstructions |= ExtraInstructions.MONITOR | ExtraInstructions.MWAIT;
            if ((info[2] & 0x10) != 0)
                Features |= CpuFeatures.CPLQualifiedDebugStore;
            if ((info[2] & 0x20) != 0)
                Features |= CpuFeatures.VirtualMachineExtensions;
            if ((info[2] & 0x40) != 0)
                Features |= CpuFeatures.SaferModeExtensions;
            if ((info[2] & 0x80) != 0)
                Features |= CpuFeatures.EnhancedIntelSpeedStepTechnology;
            if ((info[2] & 0x100) != 0)
                Features |= CpuFeatures.ThermalMonitor2;
            if ((info[2] & 0x200) != 0)
                InstructionSets |= InstructionSets.SSSE3;
            if ((info[2] & 0x300) != 0)
                Features |= CpuFeatures.L1ContextID;
            if ((info[2] & 0x1000) != 0)
                InstructionSets |= InstructionSets.FMA;
            if ((info[2] & 0x2000) != 0)
                ExtraInstructions |= ExtraInstructions.CMPXCHG16B;
            if ((info[2] & 0x4000) != 0)
                Features |= CpuFeatures.XtprUpdateControl;
            if ((info[2] & 0x8000) != 0)
                Features |= CpuFeatures.PerfDebugCapabilities;
            if ((info[2] & 0x40000) != 0)
                Features |= CpuFeatures.DirectCacheAccess;
            if ((info[2] & 0x80000) != 0)
                InstructionSets |= InstructionSets.SSE41;
            if ((info[2] & 0x100000) != 0)
                InstructionSets |= InstructionSets.SSE42;
            if ((info[2] & 0x200000) != 0)
                Features |= CpuFeatures.X2APIC;
            if ((info[2] & 0x400000) != 0)
                ExtraInstructions |= ExtraInstructions.MOVBE;
            if ((info[2] & 0x800000) != 0)
                ExtraInstructions |= ExtraInstructions.POPCNT;
            if ((info[2] & 0x2000000) != 0)
                InstructionSets |= InstructionSets.AES;
            if ((info[2] & 0x4000000) != 0)
                ExtraInstructions |= ExtraInstructions.XSAVE;
            if ((info[2] & 0x8000000) != 0)
                ExtraInstructions |= ExtraInstructions.OSXSAVE;
            if ((info[2] & 0x10000000) != 0)
                InstructionSets |= InstructionSets.AVX;

            int featureInfo = info[3];
            for (int i = 0; i < 32; i++)
            {
                int n = 1 << i;
                if ((featureInfo & n) != 0)
                {
                    switch (i)
                    {
                        case 5: ExtraInstructions |= ExtraInstructions.RDMSR | ExtraInstructions.WRMSR; break;
                        case 8: ExtraInstructions |= ExtraInstructions.CMPXCHG8B; break;
                        case 11: ExtraInstructions |= ExtraInstructions.SYSENTER | ExtraInstructions.SYSEXIT; break;
                        case 15: ExtraInstructions |= ExtraInstructions.CMOV; break;
                        case 19: ExtraInstructions |= ExtraInstructions.CFLUSH; break;
                        case 23: InstructionSets |= InstructionSets.MMX; break;
                        case 24: ExtraInstructions |= ExtraInstructions.FXSAVE | ExtraInstructions.FXRSTOR; break;
                        case 25: InstructionSets |= InstructionSets.SSE; break;
                        case 26: InstructionSets |= InstructionSets.SSE2; break;
                        default: Features |= (CpuFeatures)n; break;
                    }
                }
            }

            byte[] brand = new byte[64];
            info = NativeMethods.cpuid(0x80000000);
            long extendedIds = (uint)info[0];
            int index = 0;

            for (uint i = 0x80000000; i <= extendedIds; i++)
            {
                info = NativeMethods.cpuid(i);
                if (i >= 0x80000002 && i <= 0x80000004)
                {
                    Array.Copy(BitConverter.GetBytes(info[0]), 0, brand, index, 4); index += 4;
                    Array.Copy(BitConverter.GetBytes(info[1]), 0, brand, index, 4); index += 4;
                    Array.Copy(BitConverter.GetBytes(info[2]), 0, brand, index, 4); index += 4;
                    Array.Copy(BitConverter.GetBytes(info[3]), 0, brand, index, 4); index += 4;
                }
                else if (i == 0x80000001)
                {
                    if ((info[2] & 0x1) != 0)
                        Features |= CpuFeatures.LAHF_SAHFAvailableIn64Bit;
                    if ((info[2] & 0x2) != 0)
                        Features |= CpuFeatures.CoreMultiprocessingLegacyMode;
                    if ((info[2] & 0x4) != 0)
                        Features |= CpuFeatures.SecureVirtualMachine;
                    if ((info[2] & 0x8) != 0)
                        Features |= CpuFeatures.ExtendedAPICRegisterSpace;
                    if ((info[2] & 0x10) != 0)
                        ExtraInstructions |= ExtraInstructions.AltMovCr8;
                    if ((info[2] & 0x20) != 0)
                        ExtraInstructions |= ExtraInstructions.LZCNT;
                    if ((info[2] & 0x40) != 0)
                        InstructionSets |= InstructionSets.SSE4A;
                    if ((info[2] & 0x80) != 0)
                        Features |= CpuFeatures.MisalignedSSESupport;
                    if ((info[2] & 0x100) != 0)
                        ExtraInstructions |= ExtraInstructions.PREFETCH;
                    if ((info[2] & 0x1000) != 0)
                        ExtraInstructions |= ExtraInstructions.SKINIT | ExtraInstructions.DEV;
                    if ((info[3] & 0x800) != 0)
                        Features |= CpuFeatures.SyscallAvailableIn64Bit;
                    if ((info[3] & 0x10000) != 0)
                        Features |= CpuFeatures.ExecuteDisableBitAvailable;
                    if ((info[3] & 0x40000) != 0)
                        InstructionSets |= InstructionSets.MMXEx;
                    if ((info[3] & 0x200000) != 0)
                        ExtraInstructions |= ExtraInstructions.FFXSR;
                    if ((info[3] & 0x400000) != 0)
                        Features |= CpuFeatures.PageSupport1GB;
                    if ((info[3] & 0x8000000) != 0)
                        ExtraInstructions |= ExtraInstructions.RDTCSP;
                    if ((info[3] & 0x20000000) != 0)
                        Features |= CpuFeatures.Supports64Bit;
                    if ((info[3] & 0x40000000) != 0)
                        InstructionSets |= InstructionSets.Amd3DNowEx;
                    if ((info[3] & 0x80000000) != 0)
                        InstructionSets |= InstructionSets.Amd3DNow;
                }
            }

            if (index != 0)
                Brand = Encoding.ASCII.GetString(brand, 0, index);
        }

        public static InstructionSets GetHighestSimdLevel(InstructionSets instructionSets)
        {
            InstructionSets highest = InstructionSets.None;
            var simdSets = InstructionSets.MMX | InstructionSets.SSE | InstructionSets.SSE2 | InstructionSets.SSE3 | InstructionSets.SSSE3 | InstructionSets.SSE41 | InstructionSets.SSE42;

            foreach (var item in Enum.GetValues(typeof(InstructionSets)))
            {
                InstructionSets v = (InstructionSets)item;
                if ((simdSets & v) == 0 || (InstructionSets & v) == 0 || (instructionSets & v) == 0)
                    continue;

                highest = (InstructionSets)Math.Max((int)v, (int)highest);
            }

            return highest;
        }
    }
}
