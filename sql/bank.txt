-- phpMyAdmin SQL Dump
-- version 4.8.4
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Mar 02, 2022 at 11:54 AM
-- Server version: 10.1.37-MariaDB
-- PHP Version: 7.3.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `bank`
--
CREATE DATABASE IF NOT EXISTS `bank` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `bank`;

-- --------------------------------------------------------

--
-- Table structure for table `klient`
--

CREATE TABLE `klient` (
  `idKlienta` int(4) NOT NULL,
  `imie` varchar(15) NOT NULL,
  `nazwisko` varchar(30) NOT NULL,
  `adres` varchar(30) NOT NULL,
  `idOpiekuna` int(4) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `klient`
--

INSERT INTO `klient` (`idKlienta`, `imie`, `nazwisko`, `adres`, `idOpiekuna`) VALUES
(11, 'Piotr', 'Adamski', 'Liliowa 1', 2),
(12, 'Jan', 'Abacki', 'Nowa 2', NULL),
(13, 'Anna', 'Abacka', 'Nowa 2', NULL),
(21, 'Marek', 'Wolski', 'Rzeczna 23', NULL),
(22, 'Marek', 'Polak', 'Dobra 1', NULL),
(23, 'Antoni', 'Nowicki', 'Dobra 11', 3),
(24, 'Ewa', 'Witecka', 'Wysoka 123', 3),
(31, 'Marcin', 'Piotrowski', 'Malinowa 7', 7),
(32, 'Adam', 'Krakowiak', 'Bananowa 15', 7),
(33, 'Jan', 'Adamski', 'Kwiatowa 7', 7),
(34, 'Maria', 'Adamska', 'Kwiatowa 7', 7),
(35, 'Jan', 'Marek', 'Owocowa 17', 8),
(36, 'Ewa', 'Nowicka', 'Wodna 5', NULL),
(91, 'Julian', 'Krol', 'Zamkowa 1', NULL),
(92, 'Julia', 'Anna', 'Zamkowa 22', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `konto`
--

CREATE TABLE `konto` (
  `nrKonta` int(4) NOT NULL,
  `saldo` decimal(10,2) NOT NULL,
  `dataOtwarcia` date NOT NULL,
  `typ` char(10) NOT NULL,
  `nazwaOddzialu` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `konto`
--

INSERT INTO `konto` (`nrKonta`, `saldo`, `dataOtwarcia`, `typ`, `nazwaOddzialu`) VALUES
(111111, '1000.00', '2012-03-23', 'standard', 'Krakow1'),
(111112, '22500.00', '2012-05-14', 'standard', 'Krakow1'),
(211111, '22500.00', '2012-05-13', 'standard', 'Krakow2'),
(211112, '2100.00', '2014-01-13', 'standard', 'Krakow2'),
(211113, '5432.00', '2020-10-01', 'standard', 'Krakow2'),
(211114, '500.00', '2022-09-30', 'standard', 'Krakow2'),
(311111, '12500.00', '2017-05-13', 'standard', 'Krakow3'),
(311112, '750.00', '2018-01-20', 'standard', 'Krakow3'),
(311113, '5432.00', '2012-11-09', 'standard', 'Krakow3'),
(311114, '960.00', '2022-09-08', 'standard', 'Krakow3'),
(311115, '5960.00', '2019-07-08', 'standard', 'Krakow3');

-- --------------------------------------------------------

--
-- Table structure for table `konto_klienta`
--

CREATE TABLE `konto_klienta` (
  `idKlienta` int(4) NOT NULL,
  `nrKonta` int(4) NOT NULL,
  `dataRejestracji` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `konto_klienta`
--

INSERT INTO `konto_klienta` (`idKlienta`, `nrKonta`, `dataRejestracji`) VALUES
(11, 111112, '2012-05-14'),
(12, 111111, '2012-03-23'),
(13, 111111, '2017-04-23'),
(21, 211114, '2022-09-30'),
(22, 211113, '2020-10-01'),
(23, 211112, '2014-01-13'),
(24, 211111, '2012-05-13'),
(31, 311111, '2017-05-13'),
(32, 311112, '2018-01-20'),
(33, 311113, '2012-11-09'),
(34, 311113, '2012-11-09'),
(34, 311114, '2022-09-08'),
(35, 311115, '2019-07-08');

-- --------------------------------------------------------

--
-- Table structure for table `lokata`
--

CREATE TABLE `lokata` (
  `nrLokaty` int(4) NOT NULL,
  `kwota` decimal(10,2) NOT NULL,
  `dataOtwarcia` date NOT NULL,
  `dataZamkniecia` date DEFAULT NULL,
  `nazwaLokaty` varchar(10) NOT NULL,
  `idKlienta` int(4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `lokata`
--

INSERT INTO `lokata` (`nrLokaty`, `kwota`, `dataOtwarcia`, `dataZamkniecia`, `nazwaLokaty`, `idKlienta`) VALUES
(1, '10000.00', '2021-01-03', '2022-01-03', 'stala12', 22),
(2, '25000.00', '2022-05-21', NULL, 'stala12', 11),
(3, '50000.00', '2020-12-07', '2022-12-07', 'super', 91),
(4, '20000.00', '2023-03-01', NULL, 'super', 92),
(5, '10000.00', '2022-01-03', '2023-01-03', 'stala12', 22),
(6, '2000.00', '2023-01-10', NULL, 'super', 91),
(7, '15000.00', '2023-03-01', NULL, 'super', 91),
(8, '1000.00', '2025-02-01', '2026-01-31', 'stala12', 91),
(9, '1000.00', '2023-02-01', '2025-01-31', 'stala12', 91);

-- --------------------------------------------------------

--
-- Table structure for table `oddzialbanku`
--

CREATE TABLE `oddzialbanku` (
  `nazwaOddzialu` varchar(10) NOT NULL,
  `kraj` varchar(10) NOT NULL,
  `adres` varchar(30) NOT NULL,
  `idKierownika` int(4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `oddzialbanku`
--

INSERT INTO `oddzialbanku` (`nazwaOddzialu`, `kraj`, `adres`, `idKierownika`) VALUES
('Krakow1', 'Polska', 'Kwiatowa 5', 1),
('Krakow2', 'Polska', 'Owocowa 2', 5),
('Krakow3', 'Polska', 'Parkowa 10', 6);

-- --------------------------------------------------------

--
-- Table structure for table `operacja`
--

CREATE TABLE `operacja` (
  `nrOperacji` int(4) NOT NULL,
  `kwota` decimal(10,2) NOT NULL,
  `dataWykonania` date NOT NULL,
  `nrKonta` int(4) NOT NULL,
  `idKlienta` int(4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `operacja`
--

INSERT INTO `operacja` (`nrOperacji`, `kwota`, `dataWykonania`, `nrKonta`, `idKlienta`) VALUES
(1, '848.54', '2014-03-01', 111111, 12),
(2, '72.02', '2013-05-02', 111112, 11),
(3, '31.46', '2013-01-07', 211111, 24),
(4, '849.62', '2015-01-25', 211112, 23),
(5, '559.68', '2021-12-26', 211113, 22),
(6, '287.37', '2022-12-06', 211114, 21),
(7, '422.80', '2019-01-28', 311111, 31),
(8, '-46.82', '2018-10-19', 311112, 32),
(9, '684.46', '2013-10-29', 311113, 33),
(10, '883.36', '2024-04-28', 311114, 34),
(11, '-723.60', '2021-11-19', 311115, 35),
(12, '3315.04', '2014-02-04', 111111, 12),
(13, '2828.21', '2022-11-11', 111112, 11),
(14, '3900.62', '2013-09-12', 211111, 24),
(15, '3657.93', '2022-06-20', 211112, 23),
(16, '4395.08', '2021-12-05', 211113, 22),
(17, '-585.06', '2022-12-16', 211114, 21),
(18, '-1560.55', '2018-06-02', 311111, 31),
(19, '4384.78', '2023-01-16', 311112, 32),
(20, '4265.96', '2016-12-12', 311113, 33),
(21, '1590.20', '2023-11-08', 311114, 34),
(22, '-820.13', '2023-11-22', 311115, 35),
(23, '130.56', '2014-08-06', 111111, 12),
(24, '7.58', '2012-08-11', 111112, 11),
(25, '969.02', '2014-07-29', 211111, 24),
(26, '343.12', '2015-04-17', 211112, 23),
(27, '798.09', '2021-10-11', 211113, 22),
(28, '75.62', '2024-03-07', 211114, 21),
(29, '253.97', '2019-04-18', 311111, 31),
(30, '144.94', '2018-07-29', 311112, 32),
(31, '468.07', '2013-05-18', 311113, 33),
(32, '588.88', '2023-03-07', 311114, 34),
(33, '976.15', '2021-01-17', 311115, 35),
(34, '58.08', '2012-06-02', 111111, 12),
(35, '55.95', '2012-05-30', 111112, 11),
(36, '40.28', '2012-07-23', 211111, 24),
(37, '61.83', '2014-02-08', 211112, 23),
(38, '12.17', '2020-12-09', 211113, 22),
(39, '74.80', '2022-12-31', 211114, 21),
(40, '11.76', '2017-06-19', 311111, 31),
(41, '50.14', '2018-04-16', 311112, 32),
(42, '46.83', '2012-12-08', 311113, 33),
(43, '38.48', '2022-12-02', 311114, 34),
(44, '9.76', '2019-09-21', 311115, 35),
(45, '135.20', '2025-03-07', 211114, 21),
(46, '53.10', '20125-04-18', 311111, 31),
(47, '244.94', '2024-07-29', 311112, 32),
(48, '400.00', '2024-05-18', 311113, 33),
(49, '570.00', '2025-03-07', 311114, 34);

-- --------------------------------------------------------

--
-- Table structure for table `pracownik`
--

CREATE TABLE `pracownik` (
  `idPracownika` int(4) NOT NULL,
  `imie` varchar(15) NOT NULL,
  `nazwisko` varchar(30) NOT NULL,
  `stanowisko` varchar(20) NOT NULL,
  `nazwaOddzialu` varchar(10) DEFAULT NULL,
  `idKierownika` int(4) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pracownik`
--

INSERT INTO `pracownik` (`idPracownika`, `imie`, `nazwisko`, `stanowisko`, `nazwaOddzialu`, `idKierownika`) VALUES
(1, 'Anna', 'Nowak', 'kierownik', 'Krakow1', NULL),
(2, 'Jan', 'Kowalski', 'doradca', 'Krakow1', 1),
(3, 'Piotr', 'Nowak', 'doradca', 'Krakow2', 5),
(5, 'Jan', 'Abacki', 'kierownik', 'Krakow2', NULL),
(6, 'Adam', 'Janowski', 'kierownik', 'Krakow3', NULL),
(7, 'Ewa', 'Adamska', 'doradca', 'Krakow3', 6),
(8, 'Jan', 'Potrowski', 'doradca', 'Krakow3', 6);

-- --------------------------------------------------------

--
-- Table structure for table `rodzajlokaty`
--

CREATE TABLE `rodzajlokaty` (
  `nazwaLokaty` varchar(10) NOT NULL,
  `oprocentowanie` float(5,3) NOT NULL,
  `czasTrwania` int(2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `rodzajlokaty`
--

INSERT INTO `rodzajlokaty` (`nazwaLokaty`, `oprocentowanie`, `czasTrwania`) VALUES
('stala12', 0.200, 12),
('stala6', 0.100, 6),
('super', 0.500, 24);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `klient`
--
ALTER TABLE `klient`
  ADD PRIMARY KEY (`idKlienta`),
  ADD KEY `idOpiekuna` (`idOpiekuna`);

--
-- Indexes for table `konto`
--
ALTER TABLE `konto`
  ADD PRIMARY KEY (`nrKonta`),
  ADD KEY `nazwaOddzialu` (`nazwaOddzialu`);

--
-- Indexes for table `konto_klienta`
--
ALTER TABLE `konto_klienta`
  ADD PRIMARY KEY (`idKlienta`,`nrKonta`),
  ADD KEY `nrKonta` (`nrKonta`);

--
-- Indexes for table `lokata`
--
ALTER TABLE `lokata`
  ADD PRIMARY KEY (`nrLokaty`),
  ADD KEY `nazwaLokaty` (`nazwaLokaty`),
  ADD KEY `idKlienta` (`idKlienta`);

--
-- Indexes for table `oddzialbanku`
--
ALTER TABLE `oddzialbanku`
  ADD PRIMARY KEY (`nazwaOddzialu`),
  ADD KEY `idKierownika` (`idKierownika`);

--
-- Indexes for table `operacja`
--
ALTER TABLE `operacja`
  ADD PRIMARY KEY (`nrOperacji`),
  ADD KEY `nrKonta` (`nrKonta`),
  ADD KEY `idKlienta` (`idKlienta`);

--
-- Indexes for table `pracownik`
--
ALTER TABLE `pracownik`
  ADD PRIMARY KEY (`idPracownika`),
  ADD KEY `nazwaOddzialu` (`nazwaOddzialu`),
  ADD KEY `idKierownika` (`idKierownika`);

--
-- Indexes for table `rodzajlokaty`
--
ALTER TABLE `rodzajlokaty`
  ADD PRIMARY KEY (`nazwaLokaty`);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `klient`
--
ALTER TABLE `klient`
  ADD CONSTRAINT `klient_ibfk_1` FOREIGN KEY (`idOpiekuna`) REFERENCES `pracownik` (`idPracownika`);

--
-- Constraints for table `konto`
--
ALTER TABLE `konto`
  ADD CONSTRAINT `konto_ibfk_1` FOREIGN KEY (`nazwaOddzialu`) REFERENCES `oddzialbanku` (`nazwaOddzialu`);

--
-- Constraints for table `konto_klienta`
--
ALTER TABLE `konto_klienta`
  ADD CONSTRAINT `konto_klienta_ibfk_1` FOREIGN KEY (`idKlienta`) REFERENCES `klient` (`idKlienta`),
  ADD CONSTRAINT `konto_klienta_ibfk_2` FOREIGN KEY (`nrKonta`) REFERENCES `konto` (`nrKonta`);

--
-- Constraints for table `lokata`
--
ALTER TABLE `lokata`
  ADD CONSTRAINT `lokata_ibfk_1` FOREIGN KEY (`idKlienta`) REFERENCES `klient` (`idKlienta`),
  ADD CONSTRAINT `lokata_ibfk_2` FOREIGN KEY (`nazwaLokaty`) REFERENCES `rodzajlokaty` (`nazwaLokaty`);

--
-- Constraints for table `oddzialbanku`
--
ALTER TABLE `oddzialbanku`
  ADD CONSTRAINT `oddzialbanku_ibfk_1` FOREIGN KEY (`idKierownika`) REFERENCES `pracownik` (`idPracownika`);

--
-- Constraints for table `operacja`
--
ALTER TABLE `operacja`
  ADD CONSTRAINT `operacja_ibfk_1` FOREIGN KEY (`nrKonta`) REFERENCES `konto` (`nrKonta`),
  ADD CONSTRAINT `operacja_ibfk_2` FOREIGN KEY (`idKlienta`) REFERENCES `klient` (`idKlienta`);

--
-- Constraints for table `pracownik`
--
ALTER TABLE `pracownik`
  ADD CONSTRAINT `pracownik_ibfk_1` FOREIGN KEY (`nazwaOddzialu`) REFERENCES `oddzialbanku` (`nazwaOddzialu`),
  ADD CONSTRAINT `pracownik_ibfk_2` FOREIGN KEY (`idKierownika`) REFERENCES `pracownik` (`idPracownika`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
