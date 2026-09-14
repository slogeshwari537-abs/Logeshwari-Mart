Package: libpq[core,lz4,openssl,zlib]:x64-windows@18.4

**Host Environment**

- Host: x64-windows
- Compiler: MSVC 19.51.36257.0
- CMake Version: 4.4.3
-    vcpkg-tool version: 2026-07-27-98d7cb0cf1f4686a3e43aa5672b6230c1d56bce8
    vcpkg-scripts version: unknown

**To Reproduce**

`vcpkg install `

**Failure logs**

```
-- Found Python version '3.14.2 at C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/python/python-3.14.2-x64-1/python.exe'
-- Using meson: C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/meson-1.9.0-633807/meson.py
-- Using cached postgresql-18.4.tar.bz2
-- Cleaning sources at C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/buildtrees/libpq/src/tgresql-18-548f0c89bf.clean. Use --editable to skip cleaning for the packages you specify.
-- Extracting source C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/postgresql-18.4.tar.bz2
-- Applying patch library-linkage.diff
-- Applying patch libpq-and-client-tools.diff
-- Applying patch libintl.diff
-- Applying patch zic.diff
-- Applying patch windows/macro-def.patch
-- Applying patch windows/spin_delay.patch
-- Applying patch windows/getopt.patch
-- Using source at C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/buildtrees/libpq/src/tgresql-18-548f0c89bf.clean
-- Getting CMake variables for x64-windows
-- Loading CMake variables from C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/buildtrees/libpq/cmake-get-vars_C_CXX-x64-windows.cmake.log
-- Using cached msys2-mingw-w64-x86_64-pkgconf-1~2.5.1-1-any.pkg.tar.zst
-- Using cached msys2-msys2-runtime-3.6.5-1-x86_64.pkg.tar.zst
-- Using msys root at C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f
-- Configuring x64-windows-dbg
CMake Error at scripts/cmake/vcpkg_execute_required_process.cmake:127 (message):
    Command failed: C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/python/python-3.14.2-x64-1/python.exe -I C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/meson-1.9.0-633807/meson.py setup -Dauto_features=disabled -Dlz4=enabled -Dzlib=enabled -Dssl=openssl -DBISON=['C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/win_flex/2.5.24/win_bison.exe'] -DFLEX=['C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/win_flex/2.5.24/win_flex.exe'] -DPERL=C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/perl/5.42.2.1/perl/bin/perl.exe --backend ninja --wrap-mode nodownload -Doptimization=plain --native C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/buildtrees/libpq/meson-x64-windows-dbg.log --libdir lib --pkgconfig.relocatable -Ddebug=true --prefix C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/packages/libpq_x64-windows/debug --includedir ../include --pkg-config-path "['C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib/pkgconfig','C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/share/pkgconfig']" "-Dcmake_prefix_path=['C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug','C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows','C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/share']" C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/buildtrees/libpq/src/tgresql-18-548f0c89bf.clean
    Working Directory: C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/buildtrees/libpq/x64-windows-dbg
    Error code: 1
    See logs for more information:
      C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\config-x64-windows-dbg-meson-log.txt.log
      C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\config-x64-windows-dbg-out.log

Call Stack (most recent call first):
  C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/share/vcpkg-tool-meson/vcpkg_configure_meson.cmake:512 (vcpkg_execute_required_process)
  ports/libpq/portfile.cmake:57 (vcpkg_configure_meson)
  scripts/ports.cmake:209 (include)



```

<details><summary>C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\config-x64-windows-dbg-out.log</summary>

```
The Meson build system
Version: 1.9.0
Source dir: C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\src\tgresql-18-548f0c89bf.clean
Build dir: C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg
Build type: native build
Project name: postgresql
Project version: 18.4
C compiler for the host machine: C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 (msvc 19.51.36257 "Microsoft (R) C/C++ Optimizing Compiler Version 19.51.36257 for x64")
C linker for the host machine: C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/link.exe link 14.51.36257.0
Host machine cpu family: x86_64
Host machine cpu: x86_64
Run-time dependency threads found: YES
Library ws2_32 found: YES
Library secur32 found: YES
Program C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/perl/5.42.2.1/perl/bin/perl.exe found: YES (C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/perl/5.42.2.1/perl/bin/perl.exe)
Program python found: YES (C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\downloads\tools\python\python-3.14.2-x64-1\python.EXE)
Program C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/win_flex/2.5.24/win_flex.exe found: YES (C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/win_flex/2.5.24/win_flex.exe)
Program C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/win_flex/2.5.24/win_bison.exe found: YES 3.7.4 3.7.4 (C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/win_flex/2.5.24/win_bison.exe)
Program gsed sed found: NO
Program prove found: NO
Program tar found: YES (C:\Windows\system32\tar.EXE)
Program gzip found: NO
Program lz4 found: NO
Program openssl found: NO
Program zstd found: NO
Program dtrace skipped: feature dtrace disabled
Program config/missing found: YES (sh C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\src\tgresql-18-548f0c89bf.clean\config/missing)
Program cp found: NO
Program xmllint found: NO
Program xsltproc found: NO
Program wget found: NO
Program C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\downloads\tools\python\python-3.14.2-x64-1\python.exe found: YES (C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\downloads\tools\python\python-3.14.2-x64-1\python.exe)
Checking for size of "off_t" : -1 
Check usable header "bsd_auth.h" skipped: feature bsd_auth disabled
Check usable header "dns_sd.h" skipped: feature bonjour disabled
Compiler for language cpp skipped: feature llvm disabled
Dependency liburing skipped: feature liburing disabled
Found pkg-config: YES (C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe) 2.5.1
Run-time dependency liblz4 found: YES 1.10.0
Dependency libselinux skipped: feature selinux disabled
Dependency libsystemd skipped: feature systemd disabled
Run-time dependency openssl found: YES 3.6.4

..\src\tgresql-18-548f0c89bf.clean\meson.build:1513:10: ERROR: C header 'openssl/ssl.h' not found

A full log can be found at C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-logs\meson-log.txt
```
</details>

<details><summary>C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\config-x64-windows-dbg-meson-log.txt.log</summary>

```
Build started at 2026-09-13T22:14:22.425801
Main binary: C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\downloads\tools\python\python-3.14.2-x64-1\python.exe
Build Options: -Dauto_features=disabled -Dlz4=enabled -Dzlib=enabled -Dssl=openssl '-DBISON=['"'"'C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/win_flex/2.5.24/win_bison.exe'"'"']' '-DFLEX=['"'"'C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/win_flex/2.5.24/win_flex.exe'"'"']' -DPERL=C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/perl/5.42.2.1/perl/bin/perl.exe -Doptimization=plain -Ddebug=true '-Dcmake_prefix_path=['"'"'C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug'"'"','"'"'C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows'"'"','"'"'C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/share'"'"']' -Dprefix=C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/packages/libpq_x64-windows/debug -Dincludedir=../include -Dlibdir=lib -Dbackend=ninja -Dwrap_mode=nodownload -Dpkgconfig.relocatable=True '-Dpkg_config_path=['"'"'C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib/pkgconfig'"'"','"'"'C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/share/pkgconfig'"'"']' --native-file=C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/buildtrees/libpq/meson-x64-windows-dbg.log
Python system: Windows
The Meson build system
Version: 1.9.0
Source dir: C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\src\tgresql-18-548f0c89bf.clean
Build dir: C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg
Build type: native build
Project name: postgresql
Project version: 18.4
-----------
Detecting compiler via: `"C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe" -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 /?` -> 0
stdout:
C/C++ COMPILER OPTIONS


                              -OPTIMIZATION-

/O1 maximum optimizations (favor space) /O2 maximum optimizations (favor speed)
/Ob<n> inline expansion (default n=0)   /Od disable optimizations (default)
/Og enable global optimization          /Oi[-] enable intrinsic functions
/Os favor code space                    /Ot favor code speed
/Ox optimizations (favor speed)         
/favor:<blend|AMD64|INTEL64|ATOM> select processor to optimize for, one of:
    blend - a combination of optimizations for several different x64 processors
    AMD64 - 64-bit AMD processors
    INTEL64 - Intel(R)64 architecture processors
    ATOM - Intel(R) Atom(TM) processors

                             -CODE GENERATION-

/Gu[-] ensure distinct functions have distinct addresses
/Gw[-] separate global variables for linker
/GF enable read-only string pooling     /Gy[-] separate functions for linker
/GS[-] enable security checks           /GR[-] enable C++ RTTI
/guard:cf[-] enable CFG (control flow guard)
/guard:ehcont[-] enable EH continuation metadata (CET)
/EHs enable C++ EH (no SEH exceptions)  /EHa enable C++ EH (w/ SEH exceptions)
/EHc extern "C" defaults to nothrow     
/EHr always generate noexcept runtime termination checks
/fp:<contract|except[-]|fast|precise|strict> choose floating-point model:
    contract - consider floating-point contractions when generating code
    except[-] - consider floating-point exceptions when generating code
    fast - "fast" floating-point model; results are less predictable
    precise - "precise" floating-point model; results are predictable
    strict - "strict" floating-point model (implies /fp:except)
/Qfast_transcendentals generate inline FP intrinsics even with /fp:except
/Qspectre[-] enable mitigations for CVE 2017-5753
/Qpar[-] enable parallel code generation
/Qpar-report:1 auto-parallelizer diagnostic; indicate parallelized loops
/Qpar-report:2 auto-parallelizer diagnostic; indicate loops not parallelized
/Qvec-report:1 auto-vectorizer diagnostic; indicate vectorized loops
/Qvec-report:2 auto-vectorizer diagnostic; indicate loops not vectorized
/GL[-] enable link-time code generation 
/volatile:<iso|ms> choose volatile model:
    iso - Acquire/release semantics not guaranteed on volatile accesses
    ms  - Acquire/release semantics guaranteed on volatile accesses
/GA optimize for Windows Application    /Ge force stack checking for all funcs
/Gs[num] control stack checking calls   /Gh enable _penter function call
/GH enable _pexit function call         /GT generate fiber-safe TLS accesses
/RTC1 Enable fast checks (/RTCsu)       /RTCc Convert to smaller type checks
/RTCs Stack Frame runtime checking      /RTCu Uninitialized local usage checks
/clr[:option] compile for common language runtime, where option is:
    pure : produce IL-only output file (no native executable code)
    safe : produce IL-only verifiable output file
    netcore : produce assemblies targeting .NET Core runtime
    noAssembly : do not produce an assembly
    nostdlib : ignore the system .NET framework directory when searching for assemblies
    nostdimport : do not import any required assemblies implicitly
    initialAppDomain : enable initial AppDomain behavior of Visual C++ 2002
    implicitKeepAlive- : turn off implicit emission of System::GC::KeepAlive(this)
    char_t- : turn off metadata support for char8_t, char16_t and char32_t
    ECMAParamArray : use rules specified in ECMA-372/14.6 for overloads with parameter arrays (implied by /clr)
    ECMAParamArray- : use new rules for overloads with parameter arrays (implied by /clr:netcore)
/fsanitize=address Enable address sanitizer codegen
/homeparams Force parameters passed in registers to be written to the stack
/GZ Enable stack checks (/RTCs)         /Gv __vectorcall calling convention
(Preview) /dynamicdeopt Enable dynamic debugging; place deoptimized breakpoints and step in anywhere with on-demand function deoptimization
(Preview) /dynamicdeopt:suffix <suffix> File extension suffix for deoptimized output (default: .alt)
(Preview) /dynamicdeopt:sync Build deoptimized output after optimized output instead of in parallel
/arch:<SSE2|SSE4.2|AVX|AVX2|AVX512|AVX10.x> minimum CPU architecture requirements, one of:
   SSE2 - (default) enable use of instructions available with SSE2-enabled CPUs
   SSE4.2 - enable use of instructions available with SSE 4.2-enabled CPUs
   AVX - enable use of instructions available with AVX-enabled CPUs
   AVX2 - enable use of instructions available with AVX2-enabled CPUs
   AVX512 - enable use of instructions available with AVX-512-enabled CPUs
   AVX10.x - enable use of instructions available with AVX10.x-enabled CPUs. Valid values of x are 1 and 2
/QIntel-jcc-erratum enable mitigations for Intel JCC erratum
/Qspectre-load Enable spectre mitigations for all instructions which load memory
/Qspectre-load-cf Enable spectre mitigations for all control-flow instructions which load memory
/Qspectre-jmp[-] Enable spectre mitigations for unconditional jump instructions
/fpcvt:<IA|BC> FP to unsigned integer conversion compatibility
   IA - results compatible with VCVTTSD2USI instruction
   BC - results compatible with VS2017 and earlier compiler
/jumptablerdata Place jump tables for switch case statements in .rdata section
/vlen=<256|512> Choose vector length of either 256 or 512 for automatic code-generation
/vlen Choose default vector length based on /arch setting
(Preview) /feature:APX - enable use of instructions available with APX-enabled CPUs.

                              -OUTPUT FILES-

/Fa[file] name assembly listing file    /FA[scu] configure assembly listing
/Fd[file] name .PDB file                /Fe<file> name executable file
/Fm[file] name map file                 /Fo<file> name object file
/Fp<file> name precompiled header file  /Fr[file] name source browser file
/FR[file] name extended .SBR file       /Fi[file] name preprocessed file
/Fd: <file> name .PDB file              /Fe: <file> name executable file
/Fm: <file> name map file               /Fo: <file> name object file
/Fp: <file> name .PCH file              /FR: <file> name extended .SBR file
/Fi: <file> name preprocessed file      
/Ft<dir> location of the header files generated for #import
/doc[file] process XML documentation comments and optionally name the .xdc file

                              -PREPROCESSOR-

/AI<dir> add to assembly search path    /FU<file> import .NET assembly/module
/FU:asFriend<file> import .NET assembly/module as friend
/C don't strip comments                 /D<name>{=|#}<text> define macro
/E preprocess to stdout                 /EP preprocess to stdout, no #line
/P preprocess to file                   /Fx merge injected code to file
/FI<file> name forced include file      /U<name> remove predefined macro
/u remove all predefined macros         /I<dir> add to include search path
/X ignore "standard places"             
/PH generate #pragma file_hash when preprocessing
/PD print all macro definitions         

                                -LANGUAGE-

/std:<c++14|c++17|c++20|c++latest> C++ standard version
    c++14 - ISO/IEC 14882:2014 (default)
    c++17 - ISO/IEC 14882:2017
    c++20 - ISO/IEC 14882:2020
    c++latest - latest draft standard (feature set subject to change)
/std:<c11|c17|clatest> C standard version
    c11 - ISO/IEC 9899:2011
    c17 - ISO/IEC 9899:2018
    clatest - latest draft standard (feature set subject to change)
/permissive[-] enable some nonconforming code to compile
               (feature set subject to change) (off by default in C++20 and later)
/Za disable extensions (not recommended for C++)
/ZW enable WinRT language extensions    /Zs syntax check only
/await enable resumable functions extension
/await:strict enable standard C++20 coroutine support with earlier language versions
/constexpr:depth<N>     recursion depth limit for constexpr evaluation (default: 512)
/constexpr:backtrace<N> show N constexpr evaluations in diagnostics (default: 10)
/constexpr:steps<N>     terminate constexpr evaluation after N steps (default: 1048576)
/Zi enable debugging information        /Z7 enable old-style debug info
/Zo[-] generate richer debugging information for optimized code (on by default)
/ZH:[MD5|SHA1|SHA_256] hash algorithm for calculation of file checksum in debug info (default: SHA_256)
/Zp[n] pack structs on n-byte boundary  /Zl omit default library name in .OBJ
/vd{0|1|2} disable/enable vtordisp      /vm<x> type of pointers to members
/Zc:arg1[,arg2] language conformance, where arguments can be:
  forScope[-]           enforce Standard C++ for scoping rules
  wchar_t[-]            wchar_t is the native type, not a typedef
  auto[-]               enforce the new Standard C++ meaning for auto
  trigraphs[-]          enable trigraphs (off by default)
  rvalueCast[-]         enforce Standard C++ explicit type conversion rules
                        (on by default in C++20 or later, implied by /permissive-)
  strictStrings[-]      disable string-literal to [char|wchar_t]*
                        conversion (on by default in C++20 or later, implied by /permissive-)
  implicitNoexcept[-]   enable implicit noexcept on required functions
  threadSafeInit[-]     enable thread-safe local static initialization
  inline[-]             remove unreferenced function or data if it is
                        COMDAT or has internal linkage only (off by default)
  sizedDealloc[-]       enable C++14 global sized deallocation
                        functions (on by default)
  throwingNew[-]        assume operator new throws on failure (off by default)
  referenceBinding[-]   a temporary will not bind to a non-const
                        lvalue reference (on by default in C++20 or later, implied by /permissive-)
  twoPhase-             disable two-phase name lookup
  ternary[-]            enforce C++11 rules for conditional operator
                        (on by default in C++20 or later, implied by /permissive-)
  noexceptTypes[-]      enforce C++17 noexcept rules (on by default in C++17 or later)
  alignedNew[-]         enable C++17 alignment of dynamically allocated objects (on by default)
  hiddenFriend[-]       enforce Standard C++ hidden friend rules
                        (on by default in C++20 or later, implied by /permissive-)
  externC[-]            enforce Standard C++ rules for 'extern "C"' functions
                        (on by default in C++20 or later, implied by /permissive-)
  lambda[-]             better lambda support by using the newer lambda processor
                        (on by default in C++20 or later, implied by /permissive-)
  tlsGuards[-]          generate runtime checks for TLS variable initialization (on by default)
  zeroSizeArrayNew[-]   call member new/delete for 0-size arrays of objects (on by default)
  static_assert[-]      strict handling of 'static_assert' (on by default in C++20 or later,
                        implied by /permissive-)
  gotoScope[-]          cannot jump past the initialization of a variable (implied by /permissive-)
  templateScope[-]      enforce Standard C++ template parameter shadowing rules
  enumTypes[-]          enable Standard C++ underlying enum types (off by default)
  enumEncoding[-]       correctly encode a use of an enumeration as a non-type template
                        argument (off by default)
  checkGwOdr[-]         enforce Standard C++ one definition rule violations
                        when /Gw has been enabled (off by default)
  nrvo[-]               enable optional copy and move elision (on by default in C++20 or later,
                        implied by /permissive- or /O2)
  __STDC__              define __STDC__ to 1 in C
  __cplusplus[-]        __cplusplus macro reports the supported C++ standard (off by default)
  char8_t[-]            enable C++20 native `u8` literal support as `const char8_t`
                        (on by default in C++20 or later)
  externConstexpr[-]    enable external linkage for constexpr variables in C++
                        (on by default in C++20 or later, implied by /permissive-)
  preprocessor[-]       enable standard conforming preprocessor in C/C++
                        (on by default in C11 or later)
/ZI enable Edit and Continue debug info 
/openmp enable OpenMP 2.0 language extensions
/openmp:experimental enable OpenMP 2.0 language extensions plus select OpenMP 3.0+ language extensions
/openmp:llvm OpenMP language extensions using LLVM runtime

                              -MISCELLANEOUS-

@<file> options response file           /?, /help print this help message
/bigobj generate extended object format /c compile only, no link
/FC use full pathnames in diagnostics   /H<num> max external name length
/J default char type is unsigned        
/MP[n] use up to 'n' processes for compilation
/nologo suppress copyright message      /showIncludes show include file names
/Tc<source file> compile file as .c     /Tp<source file> compile file as .cpp
/TC compile all files as .c             /TP compile all files as .cpp
/V<string> set version string           /Yc[file] create .PCH file
/Yd put debug info in every .OBJ        /Yl[sym] inject .PCH ref for debug lib
/Yu[file] use .PCH file                 /Y- disable all PCH options
/Zm<n> max memory alloc (% of default)  /FS force to use MSPDBSRV.EXE
/source-charset:<iana-name>|.nnnn set source character set
/execution-charset:<iana-name>|.nnnn set execution character set
/utf-8 set source and execution character set to UTF-8
/validate-charset[-] validate UTF-8 files for only legal characters
/fastfail[-] enable fast-fail mode      /JMC[-] enable native just my code
/presetPadding[-] zero initialize padding for stack based class types
/volatileMetadata[-] generate metadata on volatile memory accesses
/sourcelink [file] file containing source link information
/templateDepth:N limit the depth of template instantiations (default N=1000)

                                -LINKING-

/LD Create .DLL                         /LDd Create .DLL debug library
/LN Create a .netmodule                 /F<num> set stack size
/link [linker options and libraries]    /MD link with MSVCRT.LIB
/MT link with LIBCMT.LIB                /MDd link with MSVCRTD.LIB debug lib
/MTd link with LIBCMTD.LIB debug lib    

                              -CODE ANALYSIS-

/analyze[-] Enable native analysis      /analyze:quiet[-] No warning to console
/analyze:log<name> Warnings to file     /analyze:autolog Log to *.pftlog
/analyze:autolog:ext<ext> Log to *.<ext>/analyze:autolog- No log file
/analyze:WX- Warnings not fatal         /analyze:stacksize<num> Max stack frame
/analyze:max_paths<num> Max paths       /analyze:only Analyze, no code gen

                              -DIAGNOSTICS-

/diagnostics:<args,...> controls the format of diagnostic messages:
             classic   - retains prior format
             column[-] - prints column information
             caret[-]  - prints column and the indicated line of source
/Wall enable all warnings               /w   disable all warnings
/W<n> set warning level (default n=1)   
/Wv:xx[.yy[.zzzzz]] disable warnings introduced after version xx.yy.zzzzz
/WX treat warnings as errors            /WL enable one line diagnostics
/wd<n> disable warning n                /we<n> treat warning n as an error
/wo<n> issue warning n once             /w<l><n> set warning level 1-4 for n
/external:I <path>      - location of external headers
/external:env:<var>     - environment variable with locations of external headers
/external:anglebrackets - treat all headers included via <> as external
/external:W<n>          - warning level for external headers
/external:templates[-]  - evaluate warning level across template instantiation chain
/sdl enable additional security features and warnings
/options:strict unrecognized compiler options are an error
/limitTemplateNotes:N limit the number of context messages when the compiler
                      detects a runaway template instantiation (default N=25)
-----------
stderr:
Microsoft (R) C/C++ Optimizing Compiler Version 19.51.36257 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.
-----------
Sanity testing C compiler: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe" -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1
Is cross compiler: False.
Sanity check compiler command line: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe" -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 sanitycheckc.c /Fesanitycheckc.exe /MDd -nologo -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 "-IC:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/include" /nologo /showIncludes /utf-8 /link -machine:x64 -debug -INCREMENTAL "/LIBPATH:C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib"
Sanity check compile stdout:
sanitycheckc.c

-----
Sanity check compile stderr:

-----
...
Skipped 3 lines
...
C compiler for the host machine: C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 (msvc 19.51.36257 "Microsoft (R) C/C++ Optimizing Compiler Version 19.51.36257 for x64")
C linker for the host machine: C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/link.exe link 14.51.36257.0
-----------
Detecting archiver via: `"C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/lib.exe" -machine:x64 -nologo /?` -> 1100
stdout:
usage: LIB [options] [files]

   options:

      /DEF[:filename]
      /ERRORREPORT:{NONE|PROMPT|QUEUE|SEND}
      /EXPORT:symbol
      /EXTRACT:membername
      /INCLUDE:symbol
      /LIBPATH:dir
      /LINKREPRO:dir
      /LINKREPROFULLPATHRSP:filename
      /LINKREPROTARGET:filename
      /LIST[:filename]
      /LTCG
      /MACHINE:{ARM64|ARM64X|EBC|X64|X86}
      /NAME:filename
      /NODEFAULTLIB[:library]
      /NOLOGO
      /OUT:filename
      /REMOVE:membername
      /SUBSYSTEM:{BOOT_APPLICATION|CONSOLE|EFI_APPLICATION|
                  EFI_BOOT_SERVICE_DRIVER|EFI_ROM|EFI_RUNTIME_DRIVER|
                  NATIVE|POSIX|WINDOWS|WINDOWSCE}[,#[.##]]
      /VERBOSE
      /WX[:NO]
      /WX[:nnnn[,nnnn...]]
-----------
-----------
Detecting compiler via: `"C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe" -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 /?` -> 0
stdout:
C/C++ COMPILER OPTIONS


                              -OPTIMIZATION-

/O1 maximum optimizations (favor space) /O2 maximum optimizations (favor speed)
/Ob<n> inline expansion (default n=0)   /Od disable optimizations (default)
/Og enable global optimization          /Oi[-] enable intrinsic functions
/Os favor code space                    /Ot favor code speed
/Ox optimizations (favor speed)         
/favor:<blend|AMD64|INTEL64|ATOM> select processor to optimize for, one of:
    blend - a combination of optimizations for several different x64 processors
    AMD64 - 64-bit AMD processors
    INTEL64 - Intel(R)64 architecture processors
    ATOM - Intel(R) Atom(TM) processors

                             -CODE GENERATION-

/Gu[-] ensure distinct functions have distinct addresses
/Gw[-] separate global variables for linker
/GF enable read-only string pooling     /Gy[-] separate functions for linker
/GS[-] enable security checks           /GR[-] enable C++ RTTI
/guard:cf[-] enable CFG (control flow guard)
/guard:ehcont[-] enable EH continuation metadata (CET)
/EHs enable C++ EH (no SEH exceptions)  /EHa enable C++ EH (w/ SEH exceptions)
/EHc extern "C" defaults to nothrow     
/EHr always generate noexcept runtime termination checks
/fp:<contract|except[-]|fast|precise|strict> choose floating-point model:
    contract - consider floating-point contractions when generating code
    except[-] - consider floating-point exceptions when generating code
    fast - "fast" floating-point model; results are less predictable
    precise - "precise" floating-point model; results are predictable
    strict - "strict" floating-point model (implies /fp:except)
/Qfast_transcendentals generate inline FP intrinsics even with /fp:except
/Qspectre[-] enable mitigations for CVE 2017-5753
/Qpar[-] enable parallel code generation
/Qpar-report:1 auto-parallelizer diagnostic; indicate parallelized loops
/Qpar-report:2 auto-parallelizer diagnostic; indicate loops not parallelized
/Qvec-report:1 auto-vectorizer diagnostic; indicate vectorized loops
/Qvec-report:2 auto-vectorizer diagnostic; indicate loops not vectorized
/GL[-] enable link-time code generation 
/volatile:<iso|ms> choose volatile model:
    iso - Acquire/release semantics not guaranteed on volatile accesses
    ms  - Acquire/release semantics guaranteed on volatile accesses
/GA optimize for Windows Application    /Ge force stack checking for all funcs
/Gs[num] control stack checking calls   /Gh enable _penter function call
/GH enable _pexit function call         /GT generate fiber-safe TLS accesses
/RTC1 Enable fast checks (/RTCsu)       /RTCc Convert to smaller type checks
/RTCs Stack Frame runtime checking      /RTCu Uninitialized local usage checks
/clr[:option] compile for common language runtime, where option is:
    pure : produce IL-only output file (no native executable code)
    safe : produce IL-only verifiable output file
    netcore : produce assemblies targeting .NET Core runtime
    noAssembly : do not produce an assembly
    nostdlib : ignore the system .NET framework directory when searching for assemblies
    nostdimport : do not import any required assemblies implicitly
    initialAppDomain : enable initial AppDomain behavior of Visual C++ 2002
    implicitKeepAlive- : turn off implicit emission of System::GC::KeepAlive(this)
    char_t- : turn off metadata support for char8_t, char16_t and char32_t
    ECMAParamArray : use rules specified in ECMA-372/14.6 for overloads with parameter arrays (implied by /clr)
    ECMAParamArray- : use new rules for overloads with parameter arrays (implied by /clr:netcore)
/fsanitize=address Enable address sanitizer codegen
/homeparams Force parameters passed in registers to be written to the stack
/GZ Enable stack checks (/RTCs)         /Gv __vectorcall calling convention
(Preview) /dynamicdeopt Enable dynamic debugging; place deoptimized breakpoints and step in anywhere with on-demand function deoptimization
(Preview) /dynamicdeopt:suffix <suffix> File extension suffix for deoptimized output (default: .alt)
(Preview) /dynamicdeopt:sync Build deoptimized output after optimized output instead of in parallel
/arch:<SSE2|SSE4.2|AVX|AVX2|AVX512|AVX10.x> minimum CPU architecture requirements, one of:
   SSE2 - (default) enable use of instructions available with SSE2-enabled CPUs
   SSE4.2 - enable use of instructions available with SSE 4.2-enabled CPUs
   AVX - enable use of instructions available with AVX-enabled CPUs
   AVX2 - enable use of instructions available with AVX2-enabled CPUs
   AVX512 - enable use of instructions available with AVX-512-enabled CPUs
   AVX10.x - enable use of instructions available with AVX10.x-enabled CPUs. Valid values of x are 1 and 2
/QIntel-jcc-erratum enable mitigations for Intel JCC erratum
/Qspectre-load Enable spectre mitigations for all instructions which load memory
/Qspectre-load-cf Enable spectre mitigations for all control-flow instructions which load memory
/Qspectre-jmp[-] Enable spectre mitigations for unconditional jump instructions
/fpcvt:<IA|BC> FP to unsigned integer conversion compatibility
   IA - results compatible with VCVTTSD2USI instruction
   BC - results compatible with VS2017 and earlier compiler
/jumptablerdata Place jump tables for switch case statements in .rdata section
/vlen=<256|512> Choose vector length of either 256 or 512 for automatic code-generation
/vlen Choose default vector length based on /arch setting
(Preview) /feature:APX - enable use of instructions available with APX-enabled CPUs.

                              -OUTPUT FILES-

/Fa[file] name assembly listing file    /FA[scu] configure assembly listing
/Fd[file] name .PDB file                /Fe<file> name executable file
/Fm[file] name map file                 /Fo<file> name object file
/Fp<file> name precompiled header file  /Fr[file] name source browser file
/FR[file] name extended .SBR file       /Fi[file] name preprocessed file
/Fd: <file> name .PDB file              /Fe: <file> name executable file
/Fm: <file> name map file               /Fo: <file> name object file
/Fp: <file> name .PCH file              /FR: <file> name extended .SBR file
/Fi: <file> name preprocessed file      
/Ft<dir> location of the header files generated for #import
/doc[file] process XML documentation comments and optionally name the .xdc file

                              -PREPROCESSOR-

/AI<dir> add to assembly search path    /FU<file> import .NET assembly/module
/FU:asFriend<file> import .NET assembly/module as friend
/C don't strip comments                 /D<name>{=|#}<text> define macro
/E preprocess to stdout                 /EP preprocess to stdout, no #line
/P preprocess to file                   /Fx merge injected code to file
/FI<file> name forced include file      /U<name> remove predefined macro
/u remove all predefined macros         /I<dir> add to include search path
/X ignore "standard places"             
/PH generate #pragma file_hash when preprocessing
/PD print all macro definitions         

                                -LANGUAGE-

/std:<c++14|c++17|c++20|c++latest> C++ standard version
    c++14 - ISO/IEC 14882:2014 (default)
    c++17 - ISO/IEC 14882:2017
    c++20 - ISO/IEC 14882:2020
    c++latest - latest draft standard (feature set subject to change)
/std:<c11|c17|clatest> C standard version
    c11 - ISO/IEC 9899:2011
    c17 - ISO/IEC 9899:2018
    clatest - latest draft standard (feature set subject to change)
/permissive[-] enable some nonconforming code to compile
               (feature set subject to change) (off by default in C++20 and later)
/Za disable extensions (not recommended for C++)
/ZW enable WinRT language extensions    /Zs syntax check only
/await enable resumable functions extension
/await:strict enable standard C++20 coroutine support with earlier language versions
/constexpr:depth<N>     recursion depth limit for constexpr evaluation (default: 512)
/constexpr:backtrace<N> show N constexpr evaluations in diagnostics (default: 10)
/constexpr:steps<N>     terminate constexpr evaluation after N steps (default: 1048576)
/Zi enable debugging information        /Z7 enable old-style debug info
/Zo[-] generate richer debugging information for optimized code (on by default)
/ZH:[MD5|SHA1|SHA_256] hash algorithm for calculation of file checksum in debug info (default: SHA_256)
/Zp[n] pack structs on n-byte boundary  /Zl omit default library name in .OBJ
/vd{0|1|2} disable/enable vtordisp      /vm<x> type of pointers to members
/Zc:arg1[,arg2] language conformance, where arguments can be:
  forScope[-]           enforce Standard C++ for scoping rules
  wchar_t[-]            wchar_t is the native type, not a typedef
  auto[-]               enforce the new Standard C++ meaning for auto
  trigraphs[-]          enable trigraphs (off by default)
  rvalueCast[-]         enforce Standard C++ explicit type conversion rules
                        (on by default in C++20 or later, implied by /permissive-)
  strictStrings[-]      disable string-literal to [char|wchar_t]*
                        conversion (on by default in C++20 or later, implied by /permissive-)
  implicitNoexcept[-]   enable implicit noexcept on required functions
  threadSafeInit[-]     enable thread-safe local static initialization
  inline[-]             remove unreferenced function or data if it is
                        COMDAT or has internal linkage only (off by default)
  sizedDealloc[-]       enable C++14 global sized deallocation
                        functions (on by default)
  throwingNew[-]        assume operator new throws on failure (off by default)
  referenceBinding[-]   a temporary will not bind to a non-const
                        lvalue reference (on by default in C++20 or later, implied by /permissive-)
  twoPhase-             disable two-phase name lookup
  ternary[-]            enforce C++11 rules for conditional operator
                        (on by default in C++20 or later, implied by /permissive-)
  noexceptTypes[-]      enforce C++17 noexcept rules (on by default in C++17 or later)
  alignedNew[-]         enable C++17 alignment of dynamically allocated objects (on by default)
  hiddenFriend[-]       enforce Standard C++ hidden friend rules
                        (on by default in C++20 or later, implied by /permissive-)
  externC[-]            enforce Standard C++ rules for 'extern "C"' functions
                        (on by default in C++20 or later, implied by /permissive-)
  lambda[-]             better lambda support by using the newer lambda processor
                        (on by default in C++20 or later, implied by /permissive-)
  tlsGuards[-]          generate runtime checks for TLS variable initialization (on by default)
  zeroSizeArrayNew[-]   call member new/delete for 0-size arrays of objects (on by default)
  static_assert[-]      strict handling of 'static_assert' (on by default in C++20 or later,
                        implied by /permissive-)
  gotoScope[-]          cannot jump past the initialization of a variable (implied by /permissive-)
  templateScope[-]      enforce Standard C++ template parameter shadowing rules
  enumTypes[-]          enable Standard C++ underlying enum types (off by default)
  enumEncoding[-]       correctly encode a use of an enumeration as a non-type template
                        argument (off by default)
  checkGwOdr[-]         enforce Standard C++ one definition rule violations
                        when /Gw has been enabled (off by default)
  nrvo[-]               enable optional copy and move elision (on by default in C++20 or later,
                        implied by /permissive- or /O2)
  __STDC__              define __STDC__ to 1 in C
  __cplusplus[-]        __cplusplus macro reports the supported C++ standard (off by default)
  char8_t[-]            enable C++20 native `u8` literal support as `const char8_t`
                        (on by default in C++20 or later)
  externConstexpr[-]    enable external linkage for constexpr variables in C++
                        (on by default in C++20 or later, implied by /permissive-)
  preprocessor[-]       enable standard conforming preprocessor in C/C++
                        (on by default in C11 or later)
/ZI enable Edit and Continue debug info 
/openmp enable OpenMP 2.0 language extensions
/openmp:experimental enable OpenMP 2.0 language extensions plus select OpenMP 3.0+ language extensions
/openmp:llvm OpenMP language extensions using LLVM runtime

                              -MISCELLANEOUS-

@<file> options response file           /?, /help print this help message
/bigobj generate extended object format /c compile only, no link
/FC use full pathnames in diagnostics   /H<num> max external name length
/J default char type is unsigned        
/MP[n] use up to 'n' processes for compilation
/nologo suppress copyright message      /showIncludes show include file names
/Tc<source file> compile file as .c     /Tp<source file> compile file as .cpp
/TC compile all files as .c             /TP compile all files as .cpp
/V<string> set version string           /Yc[file] create .PCH file
/Yd put debug info in every .OBJ        /Yl[sym] inject .PCH ref for debug lib
/Yu[file] use .PCH file                 /Y- disable all PCH options
/Zm<n> max memory alloc (% of default)  /FS force to use MSPDBSRV.EXE
/source-charset:<iana-name>|.nnnn set source character set
/execution-charset:<iana-name>|.nnnn set execution character set
/utf-8 set source and execution character set to UTF-8
/validate-charset[-] validate UTF-8 files for only legal characters
/fastfail[-] enable fast-fail mode      /JMC[-] enable native just my code
/presetPadding[-] zero initialize padding for stack based class types
/volatileMetadata[-] generate metadata on volatile memory accesses
/sourcelink [file] file containing source link information
/templateDepth:N limit the depth of template instantiations (default N=1000)

                                -LINKING-

/LD Create .DLL                         /LDd Create .DLL debug library
/LN Create a .netmodule                 /F<num> set stack size
/link [linker options and libraries]    /MD link with MSVCRT.LIB
/MT link with LIBCMT.LIB                /MDd link with MSVCRTD.LIB debug lib
/MTd link with LIBCMTD.LIB debug lib    

                              -CODE ANALYSIS-

/analyze[-] Enable native analysis      /analyze:quiet[-] No warning to console
/analyze:log<name> Warnings to file     /analyze:autolog Log to *.pftlog
/analyze:autolog:ext<ext> Log to *.<ext>/analyze:autolog- No log file
/analyze:WX- Warnings not fatal         /analyze:stacksize<num> Max stack frame
/analyze:max_paths<num> Max paths       /analyze:only Analyze, no code gen

                              -DIAGNOSTICS-

/diagnostics:<args,...> controls the format of diagnostic messages:
             classic   - retains prior format
             column[-] - prints column information
             caret[-]  - prints column and the indicated line of source
/Wall enable all warnings               /w   disable all warnings
/W<n> set warning level (default n=1)   
/Wv:xx[.yy[.zzzzz]] disable warnings introduced after version xx.yy.zzzzz
/WX treat warnings as errors            /WL enable one line diagnostics
/wd<n> disable warning n                /we<n> treat warning n as an error
/wo<n> issue warning n once             /w<l><n> set warning level 1-4 for n
/external:I <path>      - location of external headers
/external:env:<var>     - environment variable with locations of external headers
/external:anglebrackets - treat all headers included via <> as external
/external:W<n>          - warning level for external headers
/external:templates[-]  - evaluate warning level across template instantiation chain
/sdl enable additional security features and warnings
/options:strict unrecognized compiler options are an error
/limitTemplateNotes:N limit the number of context messages when the compiler
                      detects a runaway template instantiation (default N=25)
-----------
stderr:
Microsoft (R) C/C++ Optimizing Compiler Version 19.51.36257 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.
-----------
Sanity testing C compiler: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe" -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1
Is cross compiler: False.
Sanity check compiler command line: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe" -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 sanitycheckc.c /Fesanitycheckc.exe /MDd -nologo -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 "-IC:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/include" /nologo /showIncludes /utf-8 /link -machine:x64 -debug -INCREMENTAL "/LIBPATH:C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib"
Sanity check compile stdout:
sanitycheckc.c

-----
Sanity check compile stderr:

-----
Running test binary command:  C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\sanitycheckc.exe
-----------
Sanity check: `C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\sanitycheckc.exe` -> 0
C compiler for the build machine: C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 (msvc 19.51.36257 "Microsoft (R) C/C++ Optimizing Compiler Version 19.51.36257 for x64")
C linker for the build machine: C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/link.exe link 14.51.36257.0
-----------
Detecting archiver via: `"C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/lib.exe" -machine:x64 -nologo /?` -> 1100
stdout:
usage: LIB [options] [files]

   options:

      /DEF[:filename]
      /ERRORREPORT:{NONE|PROMPT|QUEUE|SEND}
      /EXPORT:symbol
      /EXTRACT:membername
      /INCLUDE:symbol
      /LIBPATH:dir
      /LINKREPRO:dir
      /LINKREPROFULLPATHRSP:filename
      /LINKREPROTARGET:filename
      /LIST[:filename]
      /LTCG
      /MACHINE:{ARM64|ARM64X|EBC|X64|X86}
      /NAME:filename
      /NODEFAULTLIB[:library]
      /NOLOGO
      /OUT:filename
      /REMOVE:membername
      /SUBSYSTEM:{BOOT_APPLICATION|CONSOLE|EFI_APPLICATION|
                  EFI_BOOT_SERVICE_DRIVER|EFI_ROM|EFI_RUNTIME_DRIVER|
                  NATIVE|POSIX|WINDOWS|WINDOWSCE}[,#[.##]]
      /VERBOSE
      /WX[:NO]
      /WX[:nnnn[,nnnn...]]
-----------
Build machine cpu family: x86_64
Build machine cpu: x86_64
Host machine cpu family: x86_64
Host machine cpu: x86_64
Target machine cpu family: x86_64
Target machine cpu: x86_64
Run-time dependency threads found: YES
Running compile:
Working directory:  C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmpjfcfzcwf
Code:
int main(void) { return 0; }

-----------
Command line: `"C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe" -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 -INCREMENTAL "-IC:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/include" C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmpjfcfzcwf\testfile.c /FeC:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmpjfcfzcwf\output.exe /nologo /showIncludes /utf-8 /MDd -nologo -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 /nologo /showIncludes /utf-8 /Od /Oi- ws2_32.lib /link /release /nologo -machine:x64 -debug "/LIBPATH:C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib"` -> 0
stdout:
cl : Command line warning D9030 : '/showIncludes' is incompatible with multiprocessing; ignoring /MP switch
testfile.c
-----------
Library ws2_32 found: YES
Running compile:
Working directory:  C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmpgm4vwmrk
Code:
int main(void) { return 0; }

-----------
Command line: `"C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe" -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 -INCREMENTAL "-IC:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/include" C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmpgm4vwmrk\testfile.c /FeC:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmpgm4vwmrk\output.exe /nologo /showIncludes /utf-8 /MDd -nologo -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 /nologo /showIncludes /utf-8 /Od /Oi- secur32.lib /link /release /nologo -machine:x64 -debug "/LIBPATH:C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib"` -> 0
stdout:
cl : Command line warning D9030 : '/showIncludes' is incompatible with multiprocessing; ignoring /MP switch
testfile.c
-----------
Library secur32 found: YES
Program C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/perl/5.42.2.1/perl/bin/perl.exe found: YES (C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/perl/5.42.2.1/perl/bin/perl.exe)
Program python found: YES (C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\downloads\tools\python\python-3.14.2-x64-1\python.EXE)
Program C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/win_flex/2.5.24/win_flex.exe found: YES (C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/win_flex/2.5.24/win_flex.exe)
Running command: C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/win_flex/2.5.24/win_bison.exe --version
--- stdout ---
bison (GNU Bison) 3.7.4
Written by Robert Corbett and Richard Stallman.

Copyright (C) 2020 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

--- stderr ---


Program C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/win_flex/2.5.24/win_bison.exe found: YES 3.7.4 3.7.4 (C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/win_flex/2.5.24/win_bison.exe)
Program gsed sed found: NO
Program prove found: NO
Program tar found: YES (C:\Windows\system32\tar.EXE)
Program gzip found: NO
Program lz4 found: NO
Program openssl found: NO
Program zstd found: NO
Program dtrace skipped: feature dtrace disabled
Program config/missing found: YES (sh C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\src\tgresql-18-548f0c89bf.clean\config/missing)
Program cp found: NO
Program xmllint found: NO
Program xsltproc found: NO
Running command: C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/win_flex/2.5.24/win_bison.exe --version
--- stdout ---
bison (GNU Bison) 3.7.4
Written by Robert Corbett and Richard Stallman.

Copyright (C) 2020 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

--- stderr ---


Running command: C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/win_flex/2.5.24/win_flex.exe --version
--- stdout ---
win_flex.exe 2.6.4

--- stderr ---


Program wget found: NO
Running command: C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\downloads\tools\python\python-3.14.2-x64-1\python.EXE src/tools/find_meson
--- stdout ---
meson
C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\downloads\tools\python\python-3.14.2-x64-1\python.exe
C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\downloads\tools\meson-1.9.0-633807\meson.py
--- stderr ---


Program C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\downloads\tools\python\python-3.14.2-x64-1\python.exe found: YES (C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\downloads\tools\python\python-3.14.2-x64-1\python.exe)
Running compile:
Working directory:  C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmppi4esreg
Code:

        #include<stddef.h>
        #include<stdio.h>
        int main(void) {
            printf("%ld\n", (long)(sizeof(off_t)));
            return 0;
        }
-----------
Command line: `"C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe" -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 -INCREMENTAL "-IC:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/include" C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmppi4esreg\testfile.c /FeC:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmppi4esreg\output.exe /nologo /showIncludes /utf-8 /MDd -nologo -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 /nologo /showIncludes /utf-8 /Od /Oi- kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib /link -machine:x64 -debug "/LIBPATH:C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib"` -> 2
stdout:
cl : Command line warning D9030 : '/showIncludes' is incompatible with multiprocessing; ignoring /MP switch
testfile.c
Note: including file: C:\Program Files (x86)\Windows Kits\10\include\10.0.26100.0\ucrt\stddef.h
Note: including file:  C:\Program Files (x86)\Windows Kits\10\include\10.0.26100.0\ucrt\corecrt.h
Note: including file:   C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\vcruntime.h
Note: including file:    C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\sal.h
Note: including file:     C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\concurrencysal.h
Note: including file:    C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\vadefs.h
Note: including file: C:\Program Files (x86)\Windows Kits\10\include\10.0.26100.0\ucrt\stdio.h
Note: including file:  C:\Program Files (x86)\Windows Kits\10\include\10.0.26100.0\ucrt\corecrt_wstdio.h
Note: including file:   C:\Program Files (x86)\Windows Kits\10\include\10.0.26100.0\ucrt\corecrt_stdio_config.h
C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmppi4esreg\testfile.c(5): error C2065: 'off_t': undeclared identifier
-----------
Could not compile test file C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmppi4esreg\testfile.c: 2

Checking for size of "off_t" : -1 
Check usable header "bsd_auth.h" skipped: feature bsd_auth disabled
Check usable header "dns_sd.h" skipped: feature bonjour disabled
Compiler for language cpp skipped: feature llvm disabled
Dependency liburing skipped: feature liburing disabled
Pkg-config binary for host machine specified from cross file, native file, or env var as ['C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe']
'utf-8' codec can't decode byte 0x90 in position 2: invalid start byte
Unusable script 'C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe'
Found pkg-config: YES (C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe) 2.5.1
Determining dependency 'liblz4' with pkg-config executable 'C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe'
env[PKG_CONFIG]: C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe
env[PKG_CONFIG_PATH]: C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib/pkgconfig;C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/share/pkgconfig
-----------
Called: `C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe --modversion liblz4` -> 0
stdout:
1.10.0
-----------
env[PKG_CONFIG]: C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe
env[PKG_CONFIG_PATH]: C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib/pkgconfig;C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/share/pkgconfig
-----------
Called: `C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe --cflags liblz4` -> 0
stdout:
-IC:/Users/Acer/Logeshwari\\ Mart/vcpkg_installed/x64-windows/debug/../include
-----------
env[PKG_CONFIG]: C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe
env[PKG_CONFIG_ALLOW_SYSTEM_LIBS]: 1
env[PKG_CONFIG_PATH]: C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib/pkgconfig;C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/share/pkgconfig
-----------
Called: `C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe --libs liblz4` -> 0
stdout:
-LC:/Users/Acer/Logeshwari\\ Mart/vcpkg_installed/x64-windows/debug/lib -llz4d
-----------
env[PKG_CONFIG]: C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe
env[PKG_CONFIG_PATH]: C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib/pkgconfig;C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/share/pkgconfig
-----------
Called: `C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe --libs liblz4` -> 0
stdout:
-LC:/Users/Acer/Logeshwari\\ Mart/vcpkg_installed/x64-windows/debug/lib -llz4d
-----------
Running compile:
Working directory:  C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmp85uaf7ld
Code:

        #include<stddef.h>
        #include<stdio.h>
        int main(void) {
            printf("%ld\n", (long)(sizeof(void *)));
            return 0;
        }
-----------
Command line: `"C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe" -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 -INCREMENTAL "-IC:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/include" C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmp85uaf7ld\testfile.c /FeC:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmp85uaf7ld\output.exe /nologo /showIncludes /utf-8 /MDd -nologo -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 /nologo /showIncludes /utf-8 /Od /Oi- /link -machine:x64 -debug "/LIBPATH:C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib"` -> 0
stdout:
testfile.c
Note: including file: C:\Program Files (x86)\Windows Kits\10\include\10.0.26100.0\ucrt\stddef.h
Note: including file:  C:\Program Files (x86)\Windows Kits\10\include\10.0.26100.0\ucrt\corecrt.h
Note: including file:   C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\vcruntime.h
Note: including file:    C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\sal.h
Note: including file:     C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\concurrencysal.h
Note: including file:    C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\vadefs.h
Note: including file: C:\Program Files (x86)\Windows Kits\10\include\10.0.26100.0\ucrt\stdio.h
Note: including file:  C:\Program Files (x86)\Windows Kits\10\include\10.0.26100.0\ucrt\corecrt_wstdio.h
Note: including file:   C:\Program Files (x86)\Windows Kits\10\include\10.0.26100.0\ucrt\corecrt_stdio_config.h
-----------
Program stdout:

8

Program stderr:


Run-time dependency liblz4 found: YES 1.10.0
Dependency libselinux skipped: feature selinux disabled
Dependency libsystemd skipped: feature systemd disabled
Determining dependency 'openssl' with pkg-config executable 'C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe'
env[PKG_CONFIG]: C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe
env[PKG_CONFIG_PATH]: C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib/pkgconfig;C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/share/pkgconfig
-----------
Called: `C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe --modversion openssl` -> 0
stdout:
3.6.4
-----------
env[PKG_CONFIG]: C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe
env[PKG_CONFIG_PATH]: C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib/pkgconfig;C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/share/pkgconfig
-----------
Called: `C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe --cflags openssl` -> 0
stdout:
-IC:/Users/Acer/Logeshwari\\ Mart/vcpkg_installed/x64-windows/debug/../include
-----------
env[PKG_CONFIG]: C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe
env[PKG_CONFIG_ALLOW_SYSTEM_LIBS]: 1
env[PKG_CONFIG_PATH]: C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib/pkgconfig;C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/share/pkgconfig
-----------
Called: `C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe --libs openssl` -> 0
stdout:
-LC:/Users/Acer/Logeshwari\\ Mart/vcpkg_installed/x64-windows/debug/lib -llibssl -llibcrypto
-----------
env[PKG_CONFIG]: C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe
env[PKG_CONFIG_PATH]: C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/debug/lib/pkgconfig;C:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/share/pkgconfig
-----------
Called: `C:/Users/Acer/Downloads/vcpkg-master/vcpkg-master/downloads/tools/msys2/3e71d1f8e22ab23f/mingw64/bin/pkg-config.exe --libs openssl` -> 0
stdout:
-LC:/Users/Acer/Logeshwari\\ Mart/vcpkg_installed/x64-windows/debug/lib -llibssl -llibcrypto
-----------
Run-time dependency openssl found: YES 3.6.4
Running compile:
Working directory:  C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmpk2_1irel
Code:

        #ifdef __has_include
         #if !__has_include("openssl/ssl.h")
          #error "Header 'openssl/ssl.h' could not be found"
         #endif
        #else
         #include <openssl/ssl.h>
        #endif
-----------
Command line: `"C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe" -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 "-IC:/Users/Acer/Logeshwari Mart/vcpkg_installed/x64-windows/include" -IC:/Users/Acer/Logeshwari\ C:\Users\Acer\Downloads\vcpkg-master\vcpkg-master\buildtrees\libpq\x64-windows-dbg\meson-private\tmpk2_1irel\testfile.c /nologo /showIncludes /utf-8 /EP Mart/vcpkg_installed/x64-windows/debug/../include -nologo -DWIN32 -D_WINDOWS -utf-8 -MP -MDd -Z7 -Ob0 -Od -RTC1 /nologo /showIncludes /utf-8 /EP /Od /Oi-` -> 2
stderr:
cl : Command line warning D9030 : '/EP' is incompatible with multiprocessing; ignoring /MP switch
cl : Command line warning D9030 : '/showIncludes' is incompatible with multiprocessing; ignoring /MP switch
testfile.c
include
c1: fatal error C1083: Cannot open source file: 'Mart/vcpkg_installed/x64-windows/debug/../include': No such file or directory
-----------

..\src\tgresql-18-548f0c89bf.clean\meson.build:1513:10: ERROR: C header 'openssl/ssl.h' not found
```
</details>

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "name": "logeshwarimart",
  "version-string": "0.1.0",
  "dependencies": [
    {
      "name": "drogon",
      "features": [
        "postgres"
      ]
    }
  ]
}

```
</details>
