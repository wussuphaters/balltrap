-- phpMyAdmin SQL Dump
-- version 4.7.9
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Oct 18, 2018 at 11:05 AM
-- Server version: 5.7.21
-- PHP Version: 5.6.35

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `balltrap`
--

-- --------------------------------------------------------

--
-- Table structure for table `categories`
--

DROP TABLE IF EXISTS `categories`;
CREATE TABLE IF NOT EXISTS `categories` (
  `categoryId` int(11) NOT NULL,
  `categoryName` varchar(70) NOT NULL,
  `categoryStartDate` date NOT NULL,
  `categoryEndDate` date NOT NULL,
  `categoryGenre` tinyint(4) NOT NULL,
  PRIMARY KEY (`categoryId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `categories`
--

INSERT INTO `categories` (`categoryId`, `categoryName`, `categoryStartDate`, `categoryEndDate`, `categoryGenre`) VALUES
(1, 'Cadet', '2002-01-01', '2018-08-31', 1),
(2, 'Junior', '1998-01-01', '2001-12-31', 1),
(3, 'Senior', '1963-01-01', '1997-12-31', 1),
(4, 'Vétéran', '1953-01-01', '1962-12-31', 1),
(5, 'Super Vétéran', '1900-01-01', '1952-12-31', 1),
(6, 'Cadette', '2002-01-01', '2018-08-31', 0),
(7, 'Junior Femme', '1998-01-01', '2001-12-31', 0),
(8, 'Dame', '1900-01-01', '1997-12-31', 0);

-- --------------------------------------------------------

--
-- Table structure for table `channels`
--

DROP TABLE IF EXISTS `channels`;
CREATE TABLE IF NOT EXISTS `channels` (
  `channelId` int(11) NOT NULL AUTO_INCREMENT,
  `channelNumber` int(11) NOT NULL,
  `channelName` varchar(100) NOT NULL,
  `channelNbPlat` int(11) NOT NULL,
  PRIMARY KEY (`channelId`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `channels`
--

INSERT INTO `channels` (`channelId`, `channelNumber`, `channelName`, `channelNbPlat`) VALUES
(1, 1, 'Prairie de Bamaco', 1),
(2, 2, 'Canal2', 27),
(3, 3, 'Canal3', 27),
(4, 4, 'Canal4', 27),
(5, 5, 'Canal5', 27),
(6, 6, 'Canal6', 27),
(7, 12, 'Biche oh ma biche', 27),
(8, 13, 'Test', 27),
(9, 8, 'azeo', 27),
(10, 7, 'aze', 27),
(11, 14, 'Le test du 14', 25),
(12, 10, 'La Bolette', 27),
(13, 9, 'Carpac', 11),
(14, 11, 'Je peux ?', 11),
(15, 16, 'Boli', 11),
(16, 15, 'Testco', 11);

-- --------------------------------------------------------

--
-- Table structure for table `logs`
--

DROP TABLE IF EXISTS `logs`;
CREATE TABLE IF NOT EXISTS `logs` (
  `logId` int(11) NOT NULL AUTO_INCREMENT,
  `logType` enum('CREDIT','CCOMPTE','MCOMPTE','SPORT') NOT NULL,
  `logDate` datetime NOT NULL,
  `userModified` int(11) NOT NULL,
  `userAdmin` int(11) NOT NULL,
  PRIMARY KEY (`logId`),
  KEY `fk_Log_users1_idx` (`userModified`),
  KEY `fk_Log_users2_idx` (`userAdmin`)
) ENGINE=InnoDB AUTO_INCREMENT=147 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `logs`
--

INSERT INTO `logs` (`logId`, `logType`, `logDate`, `userModified`, `userAdmin`) VALUES
(1, 'MCOMPTE', '2018-03-28 11:15:51', 1, 2),
(2, 'CREDIT', '2018-03-28 11:15:51', 1, 2),
(3, 'CCOMPTE', '2018-03-28 11:15:51', 1, 3),
(4, 'CCOMPTE', '2018-03-28 11:15:51', 2, 2),
(5, 'CCOMPTE', '2018-03-28 11:15:51', 3, 1),
(6, 'MCOMPTE', '2018-03-28 11:49:33', 2, 1),
(7, 'CREDIT', '2018-03-28 11:50:23', 2, 1),
(8, 'MCOMPTE', '2018-03-28 11:56:13', 1, 3),
(9, 'MCOMPTE', '2018-03-28 12:05:43', 1, 3),
(10, 'MCOMPTE', '2018-03-28 12:10:02', 3, 3),
(11, 'CREDIT', '2018-11-03 22:50:43', 3, 3),
(12, 'MCOMPTE', '2018-03-28 14:02:50', 2, 1),
(13, 'CCOMPTE', '2018-03-28 16:16:55', 4, 1),
(14, 'MCOMPTE', '2018-03-28 16:20:07', 4, 1),
(15, 'CCOMPTE', '2018-03-28 16:21:10', 5, 1),
(16, 'CCOMPTE', '2018-03-28 16:23:15', 6, 1),
(17, 'CREDIT', '2018-03-28 16:23:36', 6, 1),
(18, 'MCOMPTE', '2018-03-28 16:26:34', 4, 1),
(19, 'MCOMPTE', '2018-03-28 16:26:46', 4, 1),
(20, 'MCOMPTE', '2018-03-28 16:26:58', 4, 1),
(21, 'MCOMPTE', '2018-03-28 16:27:31', 4, 1),
(22, 'MCOMPTE', '2018-03-28 16:27:41', 5, 1),
(23, 'CCOMPTE', '2018-03-28 18:10:06', 7, 3),
(24, 'CREDIT', '2018-03-28 18:11:00', 7, 3),
(25, 'MCOMPTE', '2018-03-30 11:31:42', 2, 2),
(26, 'CREDIT', '2018-04-04 17:27:46', 1, 2),
(27, 'CREDIT', '2018-04-04 17:34:01', 1, 3),
(29, 'CREDIT', '2018-04-05 10:28:35', 2, 2),
(30, 'MCOMPTE', '2018-04-05 11:50:47', 5, 3),
(31, 'CREDIT', '2018-04-05 12:00:33', 1, 2),
(32, 'MCOMPTE', '2018-04-05 14:03:52', 5, 1),
(33, 'CREDIT', '2018-04-05 14:04:52', 2, 2),
(34, 'CREDIT', '2018-04-05 15:14:46', 1, 1),
(35, 'CREDIT', '2018-04-05 15:14:50', 1, 2),
(36, 'CREDIT', '2018-04-05 15:36:59', 5, 2),
(37, 'CREDIT', '2018-04-05 17:25:06', 1, 1),
(38, 'CREDIT', '2018-04-06 09:49:03', 3, 1),
(39, 'CREDIT', '2018-04-06 10:49:10', 3, 1),
(40, 'MCOMPTE', '2018-04-06 12:27:06', 5, 1),
(41, 'MCOMPTE', '2018-04-06 12:27:24', 5, 1),
(42, 'MCOMPTE', '2018-04-06 12:27:52', 5, 1),
(44, 'CREDIT', '2018-04-06 15:33:54', 5, 3),
(45, 'CREDIT', '2018-04-06 15:34:05', 1, 3),
(46, 'CREDIT', '2018-04-06 15:38:56', 1, 3),
(47, 'CREDIT', '2018-04-06 15:40:42', 1, 3),
(48, 'CREDIT', '2018-04-06 15:44:54', 2, 2),
(49, 'CREDIT', '2018-04-06 15:45:45', 1, 3),
(52, 'CREDIT', '2018-04-06 16:21:50', 1, 3),
(53, 'CREDIT', '2018-04-06 16:29:49', 2, 2),
(54, 'CREDIT', '2018-04-06 17:13:39', 2, 2),
(55, 'CREDIT', '2018-04-06 17:58:49', 1, 2),
(56, 'CREDIT', '2018-04-06 18:12:33', 2, 2),
(57, 'SPORT', '2018-04-09 10:05:18', 4, 1),
(58, 'SPORT', '2018-04-09 10:05:59', 4, 1),
(59, 'CREDIT', '2018-04-09 10:07:31', 4, 1),
(60, 'SPORT', '2018-04-09 10:10:26', 4, 1),
(61, 'SPORT', '2018-04-09 10:15:29', 4, 1),
(62, 'CREDIT', '2018-04-09 10:35:23', 1, 1),
(63, 'CREDIT', '2018-04-09 10:35:38', 2, 1),
(64, 'CREDIT', '2018-04-09 10:35:56', 3, 1),
(66, 'CCOMPTE', '2018-04-09 16:29:21', 13, 1),
(67, 'CCOMPTE', '2018-04-09 16:30:42', 14, 1),
(68, 'CCOMPTE', '2018-04-09 17:25:28', 15, 1),
(69, 'CCOMPTE', '2018-04-09 17:25:51', 16, 1),
(70, 'CREDIT', '2018-04-09 17:30:23', 13, 1),
(71, 'MCOMPTE', '2018-04-09 17:49:26', 14, 1),
(72, 'MCOMPTE', '2018-04-09 17:49:29', 14, 1),
(73, 'CCOMPTE', '2018-04-09 17:49:53', 17, 1),
(74, 'MCOMPTE', '2018-04-09 17:50:42', 14, 1),
(75, 'MCOMPTE', '2018-04-10 15:38:52', 13, 2),
(76, 'MCOMPTE', '2018-04-10 15:38:57', 13, 2),
(77, 'CREDIT', '2018-04-10 15:40:11', 13, 2),
(78, 'CREDIT', '2018-04-10 15:40:15', 13, 2),
(79, 'MCOMPTE', '2018-04-10 15:59:40', 4, 1),
(80, 'SPORT', '2018-04-10 16:06:08', 5, 2),
(81, 'CREDIT', '2018-04-10 16:21:04', 13, 2),
(82, 'CREDIT', '2018-04-10 16:21:13', 2, 2),
(83, 'MCOMPTE', '2018-04-10 16:52:54', 4, 1),
(84, 'CREDIT', '2018-04-10 16:53:02', 4, 1),
(85, 'CCOMPTE', '2018-04-10 16:53:16', 18, 2),
(86, 'MCOMPTE', '2018-04-10 16:53:19', 18, 2),
(87, 'SPORT', '2018-04-10 16:55:17', 4, 1),
(88, 'MCOMPTE', '2018-04-10 16:55:37', 14, 1),
(89, 'CREDIT', '2018-04-10 16:55:39', 14, 1),
(90, 'MCOMPTE', '2018-04-10 16:56:58', 18, 2),
(91, 'CCOMPTE', '2018-04-10 16:57:07', 19, 2),
(92, 'CCOMPTE', '2018-04-10 17:57:36', 20, 1),
(93, 'MCOMPTE', '2018-04-10 17:57:44', 20, 1),
(94, 'CCOMPTE', '2018-04-10 17:57:58', 21, 1),
(95, 'CCOMPTE', '2018-04-10 17:58:04', 22, 1),
(99, 'CREDIT', '2018-04-19 14:54:16', 1, 1),
(100, 'CREDIT', '2018-04-19 14:54:25', 1, 1),
(101, 'CREDIT', '2018-04-19 14:54:34', 5, 1),
(102, 'CREDIT', '2018-04-19 14:54:42', 7, 1),
(103, 'CREDIT', '2018-04-19 15:05:37', 5, 1),
(104, 'CREDIT', '2018-04-19 15:05:49', 7, 1),
(105, 'CREDIT', '2018-04-19 15:09:37', 5, 1),
(106, 'CREDIT', '2018-04-19 15:09:49', 7, 1),
(107, 'CREDIT', '2018-04-19 15:17:28', 5, 1),
(108, 'CREDIT', '2018-04-19 15:17:37', 7, 1),
(109, 'CREDIT', '2018-04-19 15:25:25', 5, 1),
(110, 'CREDIT', '2018-04-19 15:25:32', 7, 1),
(111, 'CREDIT', '2018-04-19 15:25:36', 7, 1),
(112, 'CREDIT', '2018-04-19 15:27:07', 5, 1),
(113, 'CREDIT', '2018-04-19 15:27:15', 7, 1),
(114, 'CREDIT', '2018-04-19 15:34:47', 7, 1),
(115, 'CREDIT', '2018-04-19 15:38:10', 5, 1),
(116, 'CREDIT', '2018-04-19 15:38:18', 7, 1),
(117, 'CREDIT', '2018-04-19 15:52:06', 7, 1),
(118, 'CREDIT', '2018-04-19 15:52:16', 5, 1),
(119, 'CREDIT', '2018-04-19 15:56:37', 5, 1),
(120, 'CREDIT', '2018-04-19 15:56:46', 7, 1),
(121, 'CREDIT', '2018-04-27 16:44:57', 5, 2),
(122, 'MCOMPTE', '2018-04-27 16:45:39', 5, 2),
(123, 'MCOMPTE', '2018-04-27 16:46:07', 5, 2),
(124, 'CREDIT', '2018-04-27 16:46:25', 7, 2),
(125, 'MCOMPTE', '2018-04-27 17:34:03', 5, 1),
(126, 'SPORT', '2018-04-27 17:34:08', 5, 1),
(127, 'CREDIT', '2018-04-27 17:34:16', 5, 1),
(128, 'CREDIT', '2018-05-02 15:21:59', 5, 1),
(131, 'CREDIT', '2018-05-02 15:22:32', 6, 1),
(134, 'CREDIT', '2018-05-02 15:22:54', 7, 1),
(135, 'CREDIT', '2018-05-04 10:13:17', 5, 1),
(136, 'MCOMPTE', '2018-05-04 17:56:47', 1, 1),
(137, 'MCOMPTE', '2018-05-04 17:58:48', 1, 1),
(138, 'CREDIT', '2018-05-14 15:19:20', 5, 1),
(139, 'CCOMPTE', '2018-05-17 17:52:17', 24, 3),
(140, 'CREDIT', '2018-05-17 17:52:32', 24, 3),
(141, 'CCOMPTE', '2018-05-17 17:55:07', 25, 3),
(142, 'CCOMPTE', '2018-05-17 17:57:33', 26, 3),
(143, 'CCOMPTE', '2018-05-17 17:59:02', 27, 3),
(144, 'CCOMPTE', '2018-05-17 18:00:28', 28, 3),
(145, 'MCOMPTE', '2018-10-03 13:05:54', 5, 1),
(146, 'MCOMPTE', '2018-10-03 13:07:09', 1, 1);

-- --------------------------------------------------------

--
-- Table structure for table `parameters`
--

DROP TABLE IF EXISTS `parameters`;
CREATE TABLE IF NOT EXISTS `parameters` (
  `parameterId` int(11) NOT NULL AUTO_INCREMENT,
  `parameterCode` varchar(45) NOT NULL,
  `parameterName` varchar(200) NOT NULL,
  `parameterValue` varchar(200) NOT NULL,
  PRIMARY KEY (`parameterId`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `parameters`
--

INSERT INTO `parameters` (`parameterId`, `parameterCode`, `parameterName`, `parameterValue`) VALUES
(1, 'nbPlat', 'Nombre de plateaux', '9'),
(3, 'defaultNbPlat', 'Nombre par défaut', '1'),
(4, 'cptType', 'Type de compteur', '0'),
(5, 'lockAccount', 'Bloquer les comptes', '0'),
(6, 'codeAdmin', 'Code pour activer le mode administrateur sur les télécommandes', 'CAFE'),
(7, 'timerReset', 'Temps avant reset', '120');

-- --------------------------------------------------------

--
-- Table structure for table `userauthentifications`
--

DROP TABLE IF EXISTS `userauthentifications`;
CREATE TABLE IF NOT EXISTS `userauthentifications` (
  `userId` int(11) NOT NULL,
  `userLogin` varchar(100) NOT NULL,
  `userPassword` varchar(500) NOT NULL,
  `userType` enum('ADMIN','MEMBRE','BUREAU','EVENT') NOT NULL,
  `userSecurityCode` varchar(500) NOT NULL,
  PRIMARY KEY (`userId`),
  KEY `fk_userAuthentifications_users_idx` (`userId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `userauthentifications`
--

INSERT INTO `userauthentifications` (`userId`, `userLogin`, `userPassword`, `userType`, `userSecurityCode`) VALUES
(1, 'Mael', '$2y$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2', 'ADMIN', '$2y$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2'),
(2, 'Jormundur', '$2y$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2', 'ADMIN', '$2y$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2'),
(3, 'Noskyra', '$2y$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2', 'ADMIN', '9deb2e07749d9f26e44548122620a6f3'),
(4, 'Gael', '$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2', 'MEMBRE', 'b9a7afcec760c2b40b452904a64396ec'),
(5, 'Guy', '$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2', 'BUREAU', '6f9d800c5fb4973d174a73631912336a'),
(6, 'Kiki', '$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2', 'MEMBRE', '$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2'),
(7, 'CR7', '$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2', 'MEMBRE', '$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2'),
(13, 'Login', 'pass', 'EVENT', '130c0be444f2c9b4852d9f8eb01e302d'),
(14, 'Telethon 2', 'pass', 'EVENT', '9aa74c2b9e594386952e785bb0b657ed'),
(15, 'Telethon 3', 'pass', 'EVENT', '12ed4616d0e9c511087b901fcaac7880'),
(16, 'Telethon 4', 'pass', 'EVENT', 'c922bc221d3d13512ac7ab0efd9ec959'),
(17, 'Telethon 5', 'pass', 'EVENT', '5df30d26da80b7af9a1aebcf3ea949b7'),
(18, 'Telethon6', 'pass', 'EVENT', 'e5711ba2c4ae6d99e99dc0a49ff70948'),
(19, 'Telethon 7', 'pass', 'EVENT', '3cf36a25cf716fc3edc0320d23c1f014'),
(20, 'Telethon 6', 'pass', 'EVENT', '50b513e1c940a5c0a248392bd865334f'),
(21, 'Telethon 9', 'pass', 'EVENT', '77334f89f0339a143c344c725b910321'),
(22, 'Telethon 10', 'pass', 'EVENT', 'feb7f9b546b5a86edc1cdca09bea9c37'),
(24, 'Login', 'pass', 'MEMBRE', '62527cf2e7dc8c96a9878ab446909d5f'),
(25, 'Login', 'pass', 'MEMBRE', '4a7e3f8c2de61f2bf24e198dce2b021d'),
(26, 'Login', 'pass', 'MEMBRE', 'ce910a94cd3668cea3a7086b3d272e7c'),
(27, 'Login', 'pass', 'MEMBRE', 'f9541973c234fafb2666da452f54fc3f'),
(28, 'Login', 'pass', 'MEMBRE', 'fca4fe7ba2a2a27545b6ddbb4e8f8c7b');

-- --------------------------------------------------------

--
-- Table structure for table `usercredits`
--

DROP TABLE IF EXISTS `usercredits`;
CREATE TABLE IF NOT EXISTS `usercredits` (
  `userId` int(11) NOT NULL,
  `creditCompak` int(11) NOT NULL,
  `creditParcours` int(11) NOT NULL,
  `creditFosse` int(11) NOT NULL,
  PRIMARY KEY (`userId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `usercredits`
--

INSERT INTO `usercredits` (`userId`, `creditCompak`, `creditParcours`, `creditFosse`) VALUES
(1, 1, 16, 7),
(2, 0, 20, 4),
(3, 3, 20, 10),
(4, 0, 9, 3),
(5, 0, 10, 15),
(6, 4, 6, 4),
(7, 5, 5, 0),
(13, 14, 58, 75),
(14, 0, 99, 0),
(15, 0, 3, 0),
(16, 0, 0, 0),
(17, 0, 0, 0),
(18, 0, 0, 0),
(19, 0, 0, 0),
(20, 0, 0, 0),
(21, 0, 0, 0),
(22, 0, 0, 0),
(24, 5, 5, 5),
(25, 0, 0, 0),
(26, 0, 0, 0),
(27, 0, 0, 0),
(28, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
CREATE TABLE IF NOT EXISTS `users` (
  `userId` int(11) NOT NULL AUTO_INCREMENT,
  `categoryId` int(11) NOT NULL,
  `userFirstName` varchar(70) NOT NULL,
  `userLastName` varchar(70) NOT NULL,
  `userMail` varchar(100) NOT NULL,
  `userAddress` varchar(65) NOT NULL,
  `userAddressSupplement` varchar(65) DEFAULT NULL,
  `userZipCode` varchar(10) NOT NULL,
  `userCity` varchar(70) NOT NULL,
  `userGenre` tinyint(4) NOT NULL,
  `userBirthdate` date NOT NULL,
  `userLicenceNumber` varchar(45) NOT NULL,
  `userLicenceYear` int(11) NOT NULL,
  `userClubFrance` tinyint(4) NOT NULL DEFAULT '0',
  `userEquipeDeFrance` varchar(45) NOT NULL DEFAULT '0',
  `userMaitreTireur` varchar(45) NOT NULL DEFAULT '0',
  `userSeniorCategory` enum('1','2','3','4') DEFAULT NULL,
  `userFixPhone` varchar(20) DEFAULT NULL,
  `userMobilePhone` varchar(20) DEFAULT NULL,
  `userCommentary` varchar(500) DEFAULT NULL,
  PRIMARY KEY (`userId`),
  KEY `fk_users_categories1_idx` (`categoryId`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`userId`, `categoryId`, `userFirstName`, `userLastName`, `userMail`, `userAddress`, `userAddressSupplement`, `userZipCode`, `userCity`, `userGenre`, `userBirthdate`, `userLicenceNumber`, `userLicenceYear`, `userClubFrance`, `userEquipeDeFrance`, `userMaitreTireur`, `userSeniorCategory`, `userFixPhone`, `userMobilePhone`, `userCommentary`) VALUES
(1, 3, 'Lucas', 'Gancel', 'lucasgancel@gmail.com', '22 Rue d\'Hérouville', 'Appartement 44', '14000', 'Caen', 1, '1998-03-30', '15426', 2018, 0, '0', '0', NULL, '0231555673', '0606946488', '12cm'),
(2, 3, 'Clément', 'Cormier', 'clementecormiergm@gmail.com', '21 Rue d\'Hérouville', 'Appartement 410', '14000', 'Caen', 1, '1996-01-05', '19842', 2018, 0, '0', '0', NULL, '0231546236', NULL, 'Beau gosse ! Le Maître, the god'),
(3, 3, 'Basile', 'Loire', 'basileloire@gmail.com', '43 Quai de Juillet', '4è étage 2e Porte Gauche', '14000', 'Caen', 1, '1997-12-26', '18452', 2018, 0, '0', '0', NULL, NULL, '0678965452', 'Homme de petite taille, inférieur à Jormundur qu\'il appelle Le maître.'),
(4, 3, 'Gael', 'Clichy', 'g.clichy@fff.fr', '25 Rue des bois', NULL, '14789', 'Verchamps', 1, '1987-12-16', '1854', 2018, 0, '0', '0', '3', '0102030405', NULL, NULL),
(5, 3, 'Guy', 'Allais', 'g.allais@cicd.biz', '8 Petite route de campagne', '', '14780', 'Anisy', 1, '1990-03-08', '19853', 2018, 0, '0', '0', '1', '0231457896', NULL, 'Très bon tireur, et en plus il est très beau, selon Lucas !!!'),
(6, 3, 'Killyan', 'Mbappé', 'kikilamagouille@gmail.com', '75 Avenue des champs élysées', NULL, '75008', 'Paris', 1, '1998-12-10', '14759863', 2018, 0, '0', '0', NULL, '0105463978', NULL, 'Ce petit homme est un génie, il a ridiculisé la Russie hier, grâce à son talent.\n\nTu iras loin Kiki'),
(7, 3, 'Cristiano', 'Ronaldo', 'cristiano.ronaldo@gmail.com', 'Dans une grande villa très chère', NULL, '11111', 'Funchal-Portugal', 1, '1985-02-05', '11111', 2018, 0, '0', '0', NULL, '0202020202', '0606060606', 'CR7 il rigole pas avec ses retournées acrobatiques'),
(13, 3, 'Telethon 1', ' ', ' ', ' ', ' ', ' ', ' ', 0, '0000-00-00', ' ', 0, 0, '0', '0', '4', NULL, NULL, 'Petit test de compte event'),
(14, 3, 'Telethon 2', ' ', ' ', ' ', ' ', ' ', ' ', 0, '0000-00-00', ' ', 0, 0, '0', '0', '4', NULL, NULL, NULL),
(15, 3, 'Telethon 3', ' ', ' ', ' ', ' ', ' ', ' ', 0, '0000-00-00', ' ', 0, 0, '0', '0', '4', NULL, NULL, NULL),
(16, 3, 'Telethon 4', ' ', ' ', ' ', ' ', ' ', ' ', 0, '0000-00-00', ' ', 0, 0, '0', '0', '4', NULL, NULL, NULL),
(17, 3, 'Telethon 5', ' ', ' ', ' ', ' ', ' ', ' ', 0, '0000-00-00', ' ', 0, 0, '0', '0', '4', NULL, NULL, NULL),
(18, 3, 'Telethon 6', ' ', ' ', ' ', ' ', ' ', ' ', 0, '0000-00-00', ' ', 0, 0, '0', '0', '4', NULL, NULL, NULL),
(19, 3, 'Telethon 7', ' ', ' ', ' ', ' ', ' ', ' ', 0, '0000-00-00', ' ', 0, 0, '0', '0', '4', NULL, NULL, NULL),
(20, 3, 'Telethon 8', ' ', ' ', ' ', ' ', ' ', ' ', 0, '0000-00-00', ' ', 0, 0, '0', '0', '4', NULL, NULL, NULL),
(21, 3, 'Telethon 9', ' ', ' ', ' ', ' ', ' ', ' ', 0, '0000-00-00', ' ', 0, 0, '0', '0', '4', NULL, NULL, NULL),
(22, 3, 'Telethon 10', ' ', ' ', ' ', ' ', ' ', ' ', 0, '0000-00-00', ' ', 0, 0, '0', '0', '4', NULL, NULL, NULL),
(24, 3, 'Guillaume', 'PICARD', 'guillaume.picard@gmail.com', '25 rue du Clos Beaumois', '', '14000', 'Caen', 1, '1997-04-06', '696969', 2018, 1, '0', '0', '4', '0202020202', '0606060606', 'Guillaume qui ne respecte pas ses 5nats !'),
(25, 3, 'Benjamin', 'Vitis', 'benji.allerlom@leroux.com', 'La rue', 'le trottoir de gauche', '14000', 'Caen', 1, '1996-05-06', '0', 2018, 0, '0', '0', '4', '0102030102', '0601060106', 'Adopteunroux.com'),
(26, 1, 'Antoine', 'PRENTOUT', 'prentoutfaitlekekeavecsonmac@hotmail.fr', 'le rue en face de celle de Vitis', NULL, '14000', 'Caen', 1, '2018-05-02', '4', 2018, 0, '0', '0', '4', '0101010101', '0101010101', NULL),
(27, 1, 'Adrien', 'CHEVALIER', 'pouet@hotmail.fr', '5 rue de Bonta', NULL, '14000', 'Caen', 1, '2018-05-01', '5', 2018, 0, '0', '0', '4', '0202020202', '0202020202', NULL),
(28, 1, 'Lucas le planqué sur grépolis', 'GANPOIVRE', 'leplanque@gmail.com', 'On sait pas il est planqué', 'surement sur une île déserte', '00000', 'Ganekeru Sama', 1, '2018-05-07', '9', 2018, 0, '0', '0', '4', '0202020202', NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `usertitles`
--

DROP TABLE IF EXISTS `usertitles`;
CREATE TABLE IF NOT EXISTS `usertitles` (
  `titleId` int(11) NOT NULL AUTO_INCREMENT,
  `userId` int(11) NOT NULL,
  `titleName` varchar(60) NOT NULL,
  PRIMARY KEY (`titleId`),
  KEY `fk_userTitles_users1_idx` (`userId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `usertokens`
--

DROP TABLE IF EXISTS `usertokens`;
CREATE TABLE IF NOT EXISTS `usertokens` (
  `tokenId` varchar(200) NOT NULL,
  `userId` int(11) NOT NULL,
  `tokenType` enum('CONNECTION') NOT NULL,
  `tokenCreation` datetime NOT NULL,
  `tokenExpiration` datetime NOT NULL,
  PRIMARY KEY (`tokenId`),
  KEY `fk_userTokens_users1` (`userId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `usertokens`
--

INSERT INTO `usertokens` (`tokenId`, `userId`, `tokenType`, `tokenCreation`, `tokenExpiration`) VALUES
('65371119e0d9d63d4060df4a17b95be6db55da4e38d334d111ae81863cdad45f33106b68a6fe3ac7e15c81b18484a5da42e97fc69b3086bb163a83788f6986cd5f41a0d61a16a4d2dd9d8894b9564cb09a16b488aa641536b51c1e45520879f84186af88', 1, 'CONNECTION', '2018-10-16 19:51:18', '2018-10-16 21:03:07');

--
-- Constraints for dumped tables
--

--
-- Constraints for table `logs`
--
ALTER TABLE `logs`
  ADD CONSTRAINT `fk_Log_users1` FOREIGN KEY (`userModified`) REFERENCES `users` (`userId`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_Log_users2` FOREIGN KEY (`userAdmin`) REFERENCES `users` (`userId`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Constraints for table `userauthentifications`
--
ALTER TABLE `userauthentifications`
  ADD CONSTRAINT `fk_userAuthentifications_users` FOREIGN KEY (`userId`) REFERENCES `users` (`userId`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Constraints for table `usercredits`
--
ALTER TABLE `usercredits`
  ADD CONSTRAINT `fk_userCredit_users1` FOREIGN KEY (`userId`) REFERENCES `users` (`userId`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Constraints for table `users`
--
ALTER TABLE `users`
  ADD CONSTRAINT `fk_users_categories1` FOREIGN KEY (`categoryId`) REFERENCES `categories` (`categoryId`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Constraints for table `usertitles`
--
ALTER TABLE `usertitles`
  ADD CONSTRAINT `fk_userTitles_users1` FOREIGN KEY (`userId`) REFERENCES `users` (`userId`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Constraints for table `usertokens`
--
ALTER TABLE `usertokens`
  ADD CONSTRAINT `fk_userTokens_users1` FOREIGN KEY (`userId`) REFERENCES `users` (`userId`) ON DELETE NO ACTION ON UPDATE NO ACTION;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
