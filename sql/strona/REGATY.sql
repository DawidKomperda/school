-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: May 31, 2026 at 06:18 PM
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

--
-- Indexes for dumped tables
--

--
-- Indexes for table `REGATY`
--
ALTER TABLE `REGATY`
  ADD PRIMARY KEY (`Id_Regat`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `REGATY`
--
ALTER TABLE `REGATY`
  MODIFY `Id_Regat` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
