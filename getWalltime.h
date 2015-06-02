// --------------------------------------------------------------------
//  $File$
//  $Revision$
//  $Date$
// --------------------------------------------------------------------
#ifndef GETWALLTIME_H
#define GETWALLTIME_H

#include <chrono>

//! Aktuelle Zeit abfragen
/*
 * \return aktuelle Zeit
 */
std::chrono::time_point<std::chrono::high_resolution_clock> getWalltime();

//! Zeitspanne zwischen den Zeitpunkten start und end berechnen
 /*!
  *  \param start Startzeitpunkt
  *  \param end  Endzeitpunkt
  *  \return Zeitspanne end - start in Millisekunden
  */
std::chrono::duration<double, std::milli> elapsedMilliSeconds(std::chrono::time_point<std::chrono::high_resolution_clock> start,
                                                                                 std::chrono::time_point<std::chrono::high_resolution_clock> end);

//! Zeitspanne zwischen den Zeitpunkten start und end berechnen
/*!
*  \param start Startzeitpunkt
*  \param end  Endzeitpunkt
*  \return Zeitspanne end - start in Sekunden
*/
std::chrono::duration<double, std::ratio<1,1>> elapsedSeconds ( std::chrono::time_point<std::chrono::high_resolution_clock> start,
    std::chrono::time_point<std::chrono::high_resolution_clock> end );

//! Ausgabe einer mit elapsedMilliSeconds bestimmten Zeitspanne auf der Konsole
void printWalltime ( std::chrono::time_point<std::chrono::high_resolution_clock> start,
                           std::chrono::time_point<std::chrono::high_resolution_clock> end );

//! Ausgabe einer mit elapsedSeconds bestimmten Zeitspanne auf der Konsole
void printWalltimeInSeconds ( std::chrono::time_point<std::chrono::high_resolution_clock> start,
                                        std::chrono::time_point<std::chrono::high_resolution_clock> end );

//! Berechnung der GigaFLOPS
/*!
 * \param numberOfCalcs Anzahl der Berechnungsvorgänge
 * \param flopPerCalc   Anzahl der FLOP pro Berechnungsvorgang
 * \param duration        Vergangene Zeit in Sekunden
 * \return GigaFLOPs, die durchgeführt wurden
 */
double countGFlops ( double numberOfCalcs, double flopPerCalc, std::chrono::duration<double, std::ratio<1, 1>> duration);

//! Ausgabe der GigaFLOPS, die für einen Benchmark verwendet wurden auf der Konsole
/*!
* \param numberOfCalcs Anzahl der Berechnungsvorgänge
* \param flopPerCalc   Anzahl der FLOP pro Berechnungsvorgang
* \param duration        Vergangene Zeit in Sekunden
* \return GigaFLOPs, die durchgeführt wurden auf der Konsole
*/
void printGFLOPs ( double numberOfCalcs, double flopPerCalc, std::chrono::duration<double, std::ratio<1, 1>> duration );
#endif