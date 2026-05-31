-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: May 31, 2026 at 09:51 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `wioslarstwo`
--

-- --------------------------------------------------------

--
-- Table structure for table `KLUBY`
--

CREATE TABLE `KLUBY` (
  `Id_Klubu` int(11) NOT NULL,
  `nazwa` varchar(255) NOT NULL,
  `miasto` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `KLUBY`
--

INSERT INTO `KLUBY` (`Id_Klubu`, `nazwa`, `miasto`) VALUES
(1, 'AZS Szczecin', 'Szczecin'),
(2, 'WTW Warszawa', 'Warszawa'),
(3, 'LOTTO Bydgostia', 'Bydgoszcz'),
(4, 'Posnania Poznań', 'Poznań'),
(5, 'AZS AWFiS Gdańsk', 'Gdańsk'),
(6, 'AZS AWF Warszawa', 'Warszawa'),
(7, 'MKS Dwójka Warszawa', 'Warszawa'),
(8, 'BTW Bydgoszcz', 'Bydgoszcz'),
(9, 'Pegaz Wrocław', 'Wrocław'),
(10, 'KTW Kalisz', 'Kalisz'),
(11, 'RTW Bydgostia Kolejarz', 'Bydgoszcz'),
(12, 'WRC Warszawa', 'Warszawa'),
(13, 'AZS UMK Toruń', 'Toruń'),
(14, 'Wioślarstwo MOS Warszawa', 'Warszawa'),
(15, 'CHTW Chełmża', 'Chełmża');

-- --------------------------------------------------------

--
-- Table structure for table `OSADA`
--

CREATE TABLE `OSADA` (
  `Id_Osady` int(11) NOT NULL,
  `Id_Klubu` int(11) NOT NULL,
  `nazwa_osady` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `OSADA`
--

INSERT INTO `OSADA` (`Id_Osady`, `Id_Klubu`, `nazwa_osady`) VALUES
(1, 1, 'AZS Szczecin - Osada A'),
(2, 2, 'WTW Warszawa - Osada B'),
(3, 1, 'Osada A'),
(4, 1, 'Osada Limit Test'),
(5, 1, 'Osada Bez Miejsca'),
(6, 1, 'Osada Próba'),
(7, 1, 'Osada Test Ref'),
(8, 3, 'Bydgostia - Osada Mistrzów'),
(9, 3, 'Bydgostia - Młodzieżówka'),
(10, 4, 'Posnania - Skiff A'),
(11, 4, 'Posnania - Dwójka B'),
(12, 5, 'Gdańsk - Osada Oceaniczna'),
(13, 6, 'AWF Warszawa - Seniorzy'),
(14, 7, 'Dwójka - Juniorzy'),
(15, 8, 'BTW Bydgoszcz - Team A'),
(16, 9, 'Pegaz - Wrocławskie Orły'),
(17, 10, 'KTW Kalisz - Kaliszanka'),
(18, 3, 'Bydgostia - Ósemka Elite'),
(19, 4, 'Posnania - Waga Lekka'),
(20, 5, 'Gdańsk - Sprinterzy'),
(21, 1, 'AZS Szczecin - Osada C'),
(22, 2, 'WTW Warszawa - Osada C'),
(23, 6, 'AWF Warszawa - Kobiety'),
(24, 4, 'Posnania - Mix'),
(25, 8, 'BTW Bydgoszcz - Juniorzy'),
(26, 13, 'UMK Toruń - Akademicy'),
(27, 13, 'UMK Toruń - Lekka Osada'),
(28, 11, 'Kolejarz - Weterani'),
(29, 12, 'WRC Warszawa - Singiel A'),
(30, 14, 'MOS Warszawa - Młoda Krew'),
(31, 15, 'CHTW Chełmża - Nadzieje'),
(32, 3, 'Bydgostia - Dwójka Podwójna'),
(33, 4, 'Posnania - Czwórka Młoda'),
(34, 1, 'AZS Szczecin - Sprint Team'),
(35, 2, 'WTW Warszawa - Waga Lekka M'),
(36, 5, 'Gdańsk - Akademicka Czwórka'),
(37, 6, 'AWF Warszawa - Nadzieje Olimpijskie'),
(38, 13, 'UMK Toruń - Dziewczęta'),
(39, 4, 'Posnania - Wojownicy'),
(40, 7, 'Dwójka Warszawa - Skiff B'),
(41, 8, 'BTW Bydgoszcz - Senior Mix'),
(42, 9, 'Pegaz Wrocław - Dolnośląskie Asy'),
(43, 10, 'KTW Kalisz - Kaliski Express'),
(44, 14, 'MOS Warszawa - Dwójka'),
(45, 12, 'WRC Warszawa - Masters');

-- --------------------------------------------------------

--
-- Table structure for table `REGATY`
--

CREATE TABLE `REGATY` (
  `Id_Regat` int(11) NOT NULL,
  `nazwa_regat` varchar(255) NOT NULL,
  `miejsce` varchar(255) DEFAULT NULL,
  `data_rozpoczecia` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `REGATY`
--

INSERT INTO `REGATY` (`Id_Regat`, `nazwa_regat`, `miejsce`, `data_rozpoczecia`) VALUES
(1, 'Regaty Gryfa 2026', 'Szczecin', '2026-05-15'),
(2, 'Regaty Testowe', 'Szczecin', '2026-05-31'),
(3, 'Mistrzostwa Polski Seniorów 2026', 'Poznań (Malta)', '2026-06-12'),
(4, 'Puchar Polski - Enea Cup 2026', 'Kruszwica', '2026-06-28'),
(5, 'Młodzieżowe Mistrzostwa Polski', 'Bydgoszcz', '2026-07-15'),
(6, 'Regaty o Puchar Bałtyku', 'Gdańsk', '2026-08-05'),
(7, 'Jesienne Regaty Kontrolne', 'Poznań (Malta)', '2026-10-10'),
(8, 'Wioślarski Puchar Świata 2026', 'Poznań (Malta)', '2026-06-19'),
(9, 'Mistrzostwa Świata Seniorów 2026', 'Lucerna', '2026-08-23'),
(10, 'Młodzieżowe Mistrzostwa Europy U23', 'Brześć', '2026-09-05'),
(11, 'Regaty o Puchar Rektora UMK', 'Toruń', '2026-05-28');

-- --------------------------------------------------------

--
-- Table structure for table `SKLAD_START`
--

CREATE TABLE `SKLAD_START` (
  `Id_Zawodnika` int(11) NOT NULL,
  `Id_Startu` int(11) NOT NULL,
  `pozycja` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `SKLAD_START`
--

INSERT INTO `SKLAD_START` (`Id_Zawodnika`, `Id_Startu`, `pozycja`) VALUES
(1, 1, '2'),
(1, 3, '2'),
(1, 6, '1'),
(1, 30, 'Szlakowy'),
(1, 34, 'Szlakowy'),
(2, 1, '1'),
(2, 3, '1'),
(2, 30, '3'),
(2, 34, '3'),
(3, 2, 'Szlakowy'),
(4, 2, 'Baks'),
(5, 3, '3'),
(6, 3, '4'),
(7, 4, '1'),
(8, 5, '1'),
(10, 7, 'Szlakowy'),
(11, 7, '3'),
(12, 11, 'Szlakowy'),
(12, 13, 'Jedynkarz'),
(12, 29, 'Szlakowy'),
(12, 35, 'Szlakowy'),
(13, 44, 'Szlakowy'),
(14, 8, 'Szlakowy'),
(14, 24, 'Jedynkarz'),
(14, 28, 'Szlakowy'),
(15, 8, '3'),
(15, 28, '3'),
(16, 10, 'Szlakowy'),
(17, 10, '3'),
(18, 14, 'Jedynkarz'),
(20, 31, 'Szlakowy'),
(22, 7, '2'),
(23, 7, 'Baks'),
(23, 11, '3'),
(24, 21, 'Szlakowy'),
(24, 27, 'Szlakowy'),
(25, 8, '2'),
(28, 31, '3'),
(29, 10, '2'),
(30, 10, 'Baks'),
(31, 11, '2'),
(32, 21, '3'),
(32, 27, '3'),
(33, 8, 'Baks'),
(36, 25, 'Jedynkarz'),
(38, 11, 'Baks'),
(38, 29, '3'),
(38, 35, '3'),
(38, 45, 'Baks'),
(39, 29, '2'),
(39, 35, '2'),
(40, 21, '2'),
(40, 44, '3'),
(41, 21, 'Baks'),
(41, 27, '2'),
(41, 44, 'Baks'),
(42, 28, '2'),
(46, 26, 'Szlakowy'),
(46, 41, 'Jedynkarz'),
(47, 26, '3'),
(48, 26, '2'),
(50, 32, 'Jedynkarz'),
(50, 36, 'Jedynkarz'),
(51, 37, 'Szlakowy'),
(53, 26, 'Baks'),
(55, 29, 'Baks'),
(55, 35, 'Baks'),
(56, 30, '2'),
(56, 34, '2'),
(58, 27, 'Baks'),
(59, 28, 'Baks'),
(60, 42, 'Jedynkarz'),
(60, 43, 'Jedynkarz'),
(60, 45, '2'),
(62, 33, 'Jedynkarz'),
(64, 31, '2'),
(66, 37, '3'),
(68, 45, 'Szlakowy'),
(69, 45, '3'),
(73, 44, '2'),
(76, 30, 'Baks'),
(76, 34, 'Baks'),
(78, 37, '2'),
(81, 37, 'Baks'),
(83, 31, 'Baks');

-- --------------------------------------------------------

--
-- Table structure for table `START`
--

CREATE TABLE `START` (
  `Id_startu` int(11) NOT NULL,
  `Id_Wyscigu` int(11) NOT NULL,
  `Id_Osady` int(11) NOT NULL,
  `czas` float DEFAULT NULL,
  `miejsce` int(11) DEFAULT NULL,
  `tor_u` varchar(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `START`
--

INSERT INTO `START` (`Id_startu`, `Id_Wyscigu`, `Id_Osady`, `czas`, `miejsce`, `tor_u`) VALUES
(1, 1, 1, 372.45, 1, 'Tor 2'),
(2, 1, 2, 375.2, 2, 'Tor 4'),
(3, 2, 3, 372.45, 1, 'Tor 2'),
(4, 6, 4, 380, 3, 'Tor 3'),
(5, 4, 5, NULL, NULL, 'Tor 5'),
(6, 5, 6, NULL, NULL, 'Tor 2'),
(7, 7, 8, 362.15, 1, 'Tor 3'),
(8, 7, 13, 365.4, 2, 'Tor 4'),
(9, 7, 16, 369.85, 3, 'Tor 2'),
(10, 8, 9, 345.1, 1, 'Tor 1'),
(11, 8, 11, 348.3, 2, 'Tor 5'),
(12, 8, 15, 352, 3, 'Tor 2'),
(13, 9, 10, 410.25, 1, 'Tor 3'),
(14, 9, 14, 415.6, 2, 'Tor 4'),
(15, 10, 8, 368, 1, 'Tor 2'),
(16, 10, 13, 371.2, 2, 'Tor 3'),
(17, 11, 9, 350.15, 1, 'Tor 4'),
(18, 11, 15, 355.9, 2, 'Tor 1'),
(19, 12, 10, 412, 1, 'Tor 3'),
(20, 12, 25, 419.45, 2, 'Tor 2'),
(21, 13, 12, 178.5, 1, 'Tor 3'),
(22, 13, 20, 181.2, 2, 'Tor 4'),
(23, 14, 17, 430.1, 1, 'Tor 2'),
(24, 15, 23, 395.3, 1, 'Tor 3'),
(25, 15, 17, 402.15, 2, 'Tor 4'),
(26, 16, 26, 358.45, 1, 'Tor 3'),
(27, 16, 36, 361.2, 2, 'Tor 4'),
(28, 16, 37, 363.9, 3, 'Tor 2'),
(29, 17, 33, 338.1, 1, 'Tor 1'),
(30, 17, 34, 340.5, 2, 'Tor 3'),
(31, 17, 42, 345, 3, 'Tor 5'),
(32, 18, 29, 415.2, 1, 'Tor 2'),
(33, 18, 40, 419.8, 2, 'Tor 4'),
(34, 19, 34, 332.15, 1, 'Tor 3'),
(35, 19, 33, 335.6, 2, 'Tor 4'),
(36, 20, 29, 402.4, 4, 'Tor 1'),
(37, 21, 30, 365.1, 1, 'Tor 2'),
(38, 21, 31, 370.3, 2, 'Tor 6'),
(39, 22, 33, 342.1, 1, 'Tor 3'),
(40, 22, 37, 346.8, 2, 'Tor 4'),
(41, 23, 27, 195.4, 1, 'Tor 3'),
(42, 23, 38, 205.15, 2, 'Tor 2'),
(43, 24, 38, 435.5, 1, 'Tor 4'),
(44, 25, 36, 382.1, 1, 'Tor 3'),
(45, 25, 26, 386.4, 2, 'Tor 2');

-- --------------------------------------------------------

--
-- Table structure for table `TYPY_LODZI`
--

CREATE TABLE `TYPY_LODZI` (
  `Id_TypuLodzi` int(11) NOT NULL,
  `nazwa_skrotowa` varchar(50) NOT NULL,
  `liczba_osob` int(11) NOT NULL,
  `czy_sternik` tinyint(1) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `TYPY_LODZI`
--

INSERT INTO `TYPY_LODZI` (`Id_TypuLodzi`, `nazwa_skrotowa`, `liczba_osob`, `czy_sternik`) VALUES
(1, '4-', 4, 0),
(2, '4x', 4, 0),
(3, '1x', 1, 0);

-- --------------------------------------------------------

--
-- Table structure for table `WYSCIGI`
--

CREATE TABLE `WYSCIGI` (
  `Id_Wyscigu` int(11) NOT NULL,
  `Id_Regat` int(11) NOT NULL,
  `Id_TypuLodzi` int(11) NOT NULL,
  `dystans` varchar(50) DEFAULT NULL,
  `kategoria_wiekowa` varchar(100) DEFAULT NULL,
  `etap` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `WYSCIGI`
--

INSERT INTO `WYSCIGI` (`Id_Wyscigu`, `Id_Regat`, `Id_TypuLodzi`, `dystans`, `kategoria_wiekowa`, `etap`) VALUES
(1, 1, 1, '2000m', 'Seniorzy', 'Finał A'),
(2, 1, 2, '2000m', 'Seniorzy', 'finał A'),
(3, 1, 3, '2000m', 'Seniorzy', NULL),
(4, 1, 3, '2000m', 'Seniorzy', 'Finał A'),
(5, 2, 2, '2000m', 'Seniorzy', 'Finał A'),
(6, 1, 3, '2000m', 'Seniorzy', 'final'),
(7, 3, 1, '2000m', 'Seniorzy', 'Finał A'),
(8, 3, 2, '2000m', 'Seniorzy', 'Finał A'),
(9, 3, 3, '2000m', 'Młodzieżowcy U23', 'Finał A'),
(10, 4, 1, '2000m', 'Seniorzy', 'Przedbieg 1'),
(11, 4, 2, '2000m', 'Seniorzy', 'Przedbieg 2'),
(12, 5, 3, '2000m', 'Młodzieżowcy U23', 'Finał A'),
(13, 6, 2, '1000m', 'Seniorzy', 'Finał A'),
(14, 7, 3, '2000m', 'Młodzieżowcy U23', 'Bieg Kontrolny 1'),
(15, 3, 3, '2000m', 'Kobiety Open', 'Finał A'),
(16, 8, 1, '2000m', 'Mężczyźni Open', 'Finał A'),
(17, 8, 2, '2000m', 'Mężczyźni Open', 'Finał A'),
(18, 8, 3, '2000m', 'Mężczyźni Open', 'Finał B'),
(19, 9, 2, '2000m', 'Seniorzy', 'Finał A'),
(20, 9, 3, '2000m', 'Seniorzy', 'Finał A'),
(21, 10, 1, '2000m', 'Młodzieżowcy U23', 'Finał A'),
(22, 10, 2, '2000m', 'Młodzieżowcy U23', 'Półfinał 1'),
(23, 11, 3, '1000m', 'Studenci', 'Finał A'),
(24, 8, 3, '2000m', 'Kobiety Waga Lekka', 'Finał A'),
(25, 9, 1, '2000m', 'Kobiety Open', 'Finał B');

-- --------------------------------------------------------

--
-- Table structure for table `ZAWODNICY`
--

CREATE TABLE `ZAWODNICY` (
  `Id_Zawodnika` int(11) NOT NULL,
  `Id_Klubu` int(11) DEFAULT NULL,
  `imie` varchar(100) NOT NULL,
  `nazwisko` varchar(100) NOT NULL,
  `data_urodzenia` date DEFAULT NULL,
  `plec` varchar(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `ZAWODNICY`
--

INSERT INTO `ZAWODNICY` (`Id_Zawodnika`, `Id_Klubu`, `imie`, `nazwisko`, `data_urodzenia`, `plec`) VALUES
(1, 1, 'Jan', 'Kowalski', '2001-04-12', 'M'),
(2, 1, 'Michał', 'Nowak', '2002-11-23', 'M'),
(3, 2, 'Kamil', 'Malinowski', '2000-01-30', 'M'),
(4, 2, 'Piotr', 'Woźniak', '2003-07-15', 'M'),
(5, 1, 'Tomasz', 'Zieliński', NULL, NULL),
(6, 1, 'Adam', 'Wiśniewski', NULL, NULL),
(7, 1, 'Jan', 'kowalski', '2000-01-01', 'M'),
(8, 1, 'Jan', 'Bez', '2000-01-01', 'M'),
(9, 1, 'Adam', 'Testowy', '2000-01-01', 'M'),
(10, 3, 'Mateusz', 'Biskup', '1994-02-10', 'M'),
(11, 3, 'Mirosław', 'Ziętarski', '1993-06-27', 'M'),
(12, 4, 'Wiktor', 'Chabel', '1989-11-23', 'M'),
(13, 5, 'Karolina', 'Naja', '1990-02-05', 'K'),
(14, 6, 'Agnieszka', 'Kobus-Zawojska', '1990-08-28', 'K'),
(15, 6, 'Marta', 'Wieliczko', '1994-10-01', 'K'),
(16, 3, 'Katarzyna', 'Zillmann', '1995-07-26', 'K'),
(17, 3, 'Maria', 'Sajdak', '1991-05-22', 'K'),
(18, 7, 'Jakub', 'Dominiczak', '1995-12-05', 'M'),
(19, 8, 'Dariusz', 'Radosz', '1986-08-13', 'M'),
(20, 9, 'Piotr', 'Juszczak', '1988-07-03', 'M'),
(21, 10, 'Marcin', 'Brzeziński', '1984-09-07', 'M'),
(22, 3, 'Mikołaj', 'Burda', '1982-07-08', 'M'),
(23, 4, 'Michał', 'Szpakowski', '1989-04-23', 'M'),
(24, 5, 'Robert', 'Fuchs', '1991-06-12', 'M'),
(25, 6, 'Bartosz', 'Modrzyński', '1996-09-11', 'M'),
(26, 7, 'Łukasz', 'Posyłajka', '1996-03-14', 'M'),
(27, 8, 'Adrian', 'Brzeziński', '1998-10-15', 'M'),
(28, 9, 'Maciej', 'Zawojski', '1992-01-21', 'M'),
(29, 3, 'Anna', 'Wierzbowska', '1990-04-11', 'K'),
(30, 3, 'Maria', 'Wierzbowska', '1995-02-13', 'K'),
(31, 4, 'Monika', 'Chabel', '1992-05-10', 'K'),
(32, 5, 'Joanna', 'Dittmann', '1992-02-09', 'K'),
(33, 6, 'Olga', 'Michalkiewicz', '1994-07-26', 'K'),
(34, 1, 'Krzysztof', 'Mikołajczewski', '1999-04-05', 'M'),
(35, 2, 'Szymon', 'Pośnik', '1993-06-15', 'M'),
(36, 10, 'Magdalena', 'Fularczyk', '1986-09-16', 'K'),
(37, 3, 'Natalia', 'Madaj', '1988-01-25', 'K'),
(38, 4, 'Patryk', 'Wojtalak', '2001-03-12', 'M'),
(39, 4, 'Oskar', 'Streich', '2001-08-19', 'M'),
(40, 5, 'Jessika', 'Sobocińska', '2002-10-04', 'K'),
(41, 5, 'Zuzanna', 'Lesner', '1999-12-14', 'K'),
(42, 6, 'Weronika', 'Kaźmierczak', '2000-01-18', 'K'),
(43, 7, 'Katarzyna', 'Boruch', '1998-05-30', 'K'),
(44, 8, 'Paulina', 'Chrzanowska', '2000-03-08', 'K'),
(45, 9, 'Barbara', 'Jęchorek', '2001-02-21', 'K'),
(46, 13, 'Daniel', 'Gajanek', '1998-03-12', 'M'),
(47, 13, 'Mirosław', 'Jackowiak', '1999-11-04', 'M'),
(48, 13, 'Oskar', 'Konieczny', '2000-05-20', 'M'),
(49, 11, 'Wojciech', 'Gutorski', '1982-05-18', 'M'),
(50, 12, 'Michał', 'Gajewski', '1995-07-07', 'M'),
(51, 14, 'Szymon', 'Krawczyk', '2003-01-15', 'M'),
(52, 15, 'Paweł', 'Kowalski', '2004-09-22', 'M'),
(53, 13, 'Radosław', 'Krymski', '1996-12-30', 'M'),
(54, 3, 'Paulina', 'Górskiej', '1997-02-14', 'K'),
(55, 4, 'Cezary', 'Litka', '2002-04-11', 'M'),
(56, 1, 'Fabian', 'Barański', '1999-05-27', 'M'),
(57, 2, 'Kasper', 'Szymaniak', '2001-08-09', 'M'),
(58, 5, 'Piotr', 'Dziewieczyński', '1999-03-06', 'M'),
(59, 6, 'Gustaw', 'Skrzypczak', '2002-10-17', 'M'),
(60, 13, 'Katarzyna', 'Malinowska', '2001-11-21', 'K'),
(61, 4, 'Jakub', 'Woźniak', '2003-02-28', 'M'),
(62, 7, 'Antoni', 'Radomiński-Lasek', '2002-06-14', 'M'),
(63, 8, 'Michał', 'Witkowski', '1999-05-05', 'M'),
(64, 9, 'Kamil', 'Sarkowski', '2000-01-11', 'M'),
(65, 10, 'Jakub', 'Aleksandrowicz', '1998-09-19', 'M'),
(66, 14, 'Zofia', 'Śmiałek', '2004-04-30', 'K'),
(67, 12, 'Maciej', 'Koperski', '1985-11-12', 'M'),
(68, 13, 'Julia', 'Weiwer', '2002-05-14', 'K'),
(69, 13, 'Dominika', 'Gałka', '2002-07-19', 'K'),
(70, 3, 'Krzysztof', 'Zentner', '2000-12-01', 'M'),
(71, 3, 'Artur', 'Mikołajczewski', '1990-06-27', 'M'),
(72, 4, 'Jerzy', 'Kowalski', '1988-02-22', 'M'),
(73, 5, 'Martyna', 'Radosz', '1995-01-29', 'K'),
(74, 6, 'Katarzyna', 'Wełna', '1994-03-06', 'K'),
(75, 11, 'Mikołaj', 'Januszewski', '2001-04-18', 'M'),
(76, 1, 'Łukasz', 'Zub', '1995-09-09', 'M'),
(77, 2, 'Dominik', 'Czaja', '1995-08-12', 'M'),
(78, 14, 'Mateusz', 'Wilangowski', '1991-10-07', 'M'),
(79, 13, 'Igor', 'Malinowski', '2001-02-15', 'M'),
(80, 15, 'Adrianna', 'Paszkowska', '2002-08-08', 'K'),
(81, 7, 'Jan', 'Domeradzki', '2003-11-20', 'M'),
(82, 8, 'Małgorzata', 'Krzemińska', '1999-06-01', 'K'),
(83, 9, 'Tomasz', 'Lewandowicz', '1997-12-12', 'M'),
(84, 10, 'Weronika', 'Ludwiczak', '2002-03-31', 'K'),
(85, 12, 'Andrzej', 'Marek', '1980-01-01', 'M');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `KLUBY`
--
ALTER TABLE `KLUBY`
  ADD PRIMARY KEY (`Id_Klubu`);

--
-- Indexes for table `OSADA`
--
ALTER TABLE `OSADA`
  ADD PRIMARY KEY (`Id_Osady`),
  ADD KEY `fk_osada_klub` (`Id_Klubu`);

--
-- Indexes for table `REGATY`
--
ALTER TABLE `REGATY`
  ADD PRIMARY KEY (`Id_Regat`);

--
-- Indexes for table `SKLAD_START`
--
ALTER TABLE `SKLAD_START`
  ADD PRIMARY KEY (`Id_Zawodnika`,`Id_Startu`),
  ADD KEY `fk_sklad_start` (`Id_Startu`);

--
-- Indexes for table `START`
--
ALTER TABLE `START`
  ADD PRIMARY KEY (`Id_startu`),
  ADD KEY `fk_start_wyscig` (`Id_Wyscigu`),
  ADD KEY `fk_start_osada` (`Id_Osady`);

--
-- Indexes for table `TYPY_LODZI`
--
ALTER TABLE `TYPY_LODZI`
  ADD PRIMARY KEY (`Id_TypuLodzi`);

--
-- Indexes for table `WYSCIGI`
--
ALTER TABLE `WYSCIGI`
  ADD PRIMARY KEY (`Id_Wyscigu`),
  ADD KEY `fk_wyscig_regaty` (`Id_Regat`),
  ADD KEY `fk_wyscig_typ` (`Id_TypuLodzi`);

--
-- Indexes for table `ZAWODNICY`
--
ALTER TABLE `ZAWODNICY`
  ADD PRIMARY KEY (`Id_Zawodnika`),
  ADD KEY `fk_zawodnik_klub` (`Id_Klubu`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `KLUBY`
--
ALTER TABLE `KLUBY`
  MODIFY `Id_Klubu` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=16;

--
-- AUTO_INCREMENT for table `OSADA`
--
ALTER TABLE `OSADA`
  MODIFY `Id_Osady` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=46;

--
-- AUTO_INCREMENT for table `REGATY`
--
ALTER TABLE `REGATY`
  MODIFY `Id_Regat` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;

--
-- AUTO_INCREMENT for table `START`
--
ALTER TABLE `START`
  MODIFY `Id_startu` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=46;

--
-- AUTO_INCREMENT for table `TYPY_LODZI`
--
ALTER TABLE `TYPY_LODZI`
  MODIFY `Id_TypuLodzi` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `WYSCIGI`
--
ALTER TABLE `WYSCIGI`
  MODIFY `Id_Wyscigu` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=26;

--
-- AUTO_INCREMENT for table `ZAWODNICY`
--
ALTER TABLE `ZAWODNICY`
  MODIFY `Id_Zawodnika` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=86;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `OSADA`
--
ALTER TABLE `OSADA`
  ADD CONSTRAINT `fk_osada_klub` FOREIGN KEY (`Id_Klubu`) REFERENCES `KLUBY` (`Id_Klubu`);

--
-- Constraints for table `SKLAD_START`
--
ALTER TABLE `SKLAD_START`
  ADD CONSTRAINT `fk_sklad_start` FOREIGN KEY (`Id_Startu`) REFERENCES `START` (`Id_startu`),
  ADD CONSTRAINT `fk_sklad_zawodnik` FOREIGN KEY (`Id_Zawodnika`) REFERENCES `ZAWODNICY` (`Id_Zawodnika`);

--
-- Constraints for table `START`
--
ALTER TABLE `START`
  ADD CONSTRAINT `fk_start_osada` FOREIGN KEY (`Id_Osady`) REFERENCES `OSADA` (`Id_Osady`),
  ADD CONSTRAINT `fk_start_wyscig` FOREIGN KEY (`Id_Wyscigu`) REFERENCES `WYSCIGI` (`Id_Wyscigu`);

--
-- Constraints for table `WYSCIGI`
--
ALTER TABLE `WYSCIGI`
  ADD CONSTRAINT `fk_wyscig_regaty` FOREIGN KEY (`Id_Regat`) REFERENCES `REGATY` (`Id_Regat`),
  ADD CONSTRAINT `fk_wyscig_typ` FOREIGN KEY (`Id_TypuLodzi`) REFERENCES `TYPY_LODZI` (`Id_TypuLodzi`);

--
-- Constraints for table `ZAWODNICY`
--
ALTER TABLE `ZAWODNICY`
  ADD CONSTRAINT `fk_zawodnik_klub` FOREIGN KEY (`Id_Klubu`) REFERENCES `KLUBY` (`Id_Klubu`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
