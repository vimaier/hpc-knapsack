/// --------------------------------------------------------------------
//  Implementierung
// --------------------------------------------------------------------
#include <iostream>
#include <iomanip>

#include "getWalltime.h"

// Implementierung
 std::chrono::time_point<std::chrono::high_resolution_clock> getWalltime()
{
       return std::chrono::high_resolution_clock::now();
}

// Berechnung der Dauer für zwei Zeitpunkte. 
// Als Einheit werden Millisekunden verwendet.
std::chrono::duration<double, std::milli> elapsedMilliSeconds(std::chrono::time_point<std::chrono::high_resolution_clock> start,
                                                                        std::chrono::time_point<std::chrono::high_resolution_clock> end)
{
         std::chrono::duration<double, std::milli> elap = end - start;
         return elap;
}

// Berechnung der Dauer für zwei Zeitpunkte. 
// Als Einheit werden Sekunden verwendet.
std::chrono::duration<double, std::ratio<1, 1>>  elapsedSeconds ( std::chrono::time_point<std::chrono::high_resolution_clock> start,
    std::chrono::time_point<std::chrono::high_resolution_clock> end )
{
    std::chrono::duration<double, std::ratio<1, 1>>  elap = end - start;
    return elap;
}

// Ausgabe einer mit elapsedSeconds bestimmten Zeitspanne auf der Konsole
void printWalltime ( std::chrono::time_point<std::chrono::high_resolution_clock> start,
                          std::chrono::time_point<std::chrono::high_resolution_clock> end )
{
    std::cout << std::fixed << std::setprecision ( 2 )
                 << "Die Laufzeit: " << elapsedMilliSeconds ( start, end ).count ( )
                  << " Millisekunden" << std::endl;
}

// Ausgabe einer mit elapsedSeconds bestimmten Zeitspanne auf der Konsole
void printWalltimeInSeconds ( std::chrono::time_point<std::chrono::high_resolution_clock> start,
    std::chrono::time_point<std::chrono::high_resolution_clock> end )
{
    std::cout << std::fixed << std::setprecision (4 )
        << "Die Laufzeit: " << elapsedSeconds ( start, end ).count ()
        << " Sekunden" << std::endl;
}

// Berechnung der GigaFLOPS
double countGFlops ( double numberOfCalcs, double flopPerCalc, std::chrono::duration<double, std::ratio<1, 1>> duration )
{
    return (1.0E-9 * numberOfCalcs * flopPerCalc ) / duration.count ( );
}

// Ausgabe der GigaFLOPS, die für einen Benchmark verwendet wurden
void printGFLOPs ( double numberOfCalcs, double flopPerCalc, std::chrono::duration<double, std::ratio<1, 1>> duration )
{
    double count =  ( 1.0E-9 * numberOfCalcs * flopPerCalc ) / duration.count ( );
    std::cout << std::fixed << "Erreichte Performanz: " << count << " GFLOPs" << std::endl;
}

