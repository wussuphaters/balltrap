-- phpMyAdmin SQL Dump
-- version 4.8.3
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1:3306
-- Généré le :  Dim 24 mars 2019 à 11:43
-- Version du serveur :  5.7.23
-- Version de PHP :  7.2.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `balltrap`
--

-- --------------------------------------------------------

--
-- Structure de la table `categories`
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
-- Déchargement des données de la table `categories`
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
-- Structure de la table `channels`
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
-- Déchargement des données de la table `channels`
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
-- Structure de la table `logs`
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

-- --------------------------------------------------------

--
-- Structure de la table `parameters`
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
-- Déchargement des données de la table `parameters`
--

INSERT INTO `parameters` (`parameterId`, `parameterCode`, `parameterName`, `parameterValue`) VALUES
(1, 'nbPlat', 'Nombre de plateaux', '28'),
(2, 'multipleCards', 'Autorisation (1) ou non (0) des cartes multiples', '0'),
(3, 'defaultNbPlat', 'Nombre par défaut', '1'),
(4, 'timeout_rafale', 'Temps en secondes entre les 2 tirs d\'une rafale', '4'),
(5, 'lockAccount', 'Bloquer les comptes', '0'),
(6, 'codeAdmin', 'Code pour activer le mode administrateur sur les télécommandes', 'CAFE'),
(7, 'timerReset', 'Temps avant reset', '120');

-- --------------------------------------------------------

--
-- Structure de la table `userauthentifications`
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
-- Déchargement des données de la table `userauthentifications`
--

INSERT INTO `userauthentifications` (`userId`, `userLogin`, `userPassword`, `userType`, `userSecurityCode`) VALUES
(1, 'Guy', '$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2', 'BUREAU', '6f9d800c5fb4973d174a73631912336a'),
(2, 'Mael', '$2y$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2', 'ADMIN', '$2y$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2'),
(3, 'Basile', '$2y$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2', 'MEMBRE', '9deb2e07749d9f26e44548122620a6f3'),
(4, 'Sovanarit', '$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2', 'MEMBRE', 'b9a7afcec760c2b40b452904a64396ec'),
(5, 'Alexis', '$10$tgpvG046VDx1E6nr6MLGbOPIpIlzNAtCqsxipeYQT5MsQ8UgqJjF2', 'MEMBRE', '6f9d800c5fb4973d174a73631912336a');

-- --------------------------------------------------------

--
-- Structure de la table `usercredits`
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
-- Déchargement des données de la table `usercredits`
--

INSERT INTO `usercredits` (`userId`, `creditCompak`, `creditParcours`, `creditFosse`) VALUES
(1, 100, 100, 100),
(2, 100, 100, 100),
(3, 100, 100, 100),
(4, 100, 100, 100),
(5, 100, 100, 100);

-- --------------------------------------------------------

--
-- Structure de la table `users`
--

DROP TABLE IF EXISTS `users`;
CREATE TABLE IF NOT EXISTS `users` (
  `userId` int(11) NOT NULL AUTO_INCREMENT,
  `userRFIDTagNumber` int(20) NOT NULL,
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
-- Déchargement des données de la table `users`
--

INSERT INTO `users` (`userId`, `userRFIDTagNumber`, `categoryId`, `userFirstName`, `userLastName`, `userMail`, `userAddress`, `userAddressSupplement`, `userZipCode`, `userCity`, `userGenre`, `userBirthdate`, `userLicenceNumber`, `userLicenceYear`, `userClubFrance`, `userEquipeDeFrance`, `userMaitreTireur`, `userSeniorCategory`, `userFixPhone`, `userMobilePhone`, `userCommentary`) VALUES
(1, 16675326, 3, 'Guy', 'Allais', 'g.allais@cicd.biz', '8 Petite route de campagne', '', '14780', 'Anisy', 1, '1990-03-08', '19853', 2019, 0, '0', '0', '1', '0231457896', NULL, 'Le patron'),
(2, 14589392, 1, 'Mael', 'Ponchant', 'mael.ponchant@outlook.com', '6 Rue Anton Tchekhov', '', '14123', 'Ifs', 1, '1999-12-12', '19854', 2019, 0, '0', '0', '1', '0646705811', NULL, 'Développeur de qualité'),
(3, 15150663, 3, 'Basile', 'Loire', 'basileloire@gmail.com', '43 Quai de Juillet', '4è étage 2e Porte Gauche', '14000', 'Caen', 1, '1997-12-26', '18452', 2018, 0, '0', '0', NULL, NULL, '0678965452', 'Homme de petite taille, inférieur à Jormundur qu\'il appelle Le maître.'),
(4, 14572399, 3, 'Sovanarit', 'Long', 'sova.chinois@gmail.com', '25 Rue des bois', NULL, '14789', 'Verchamps', 1, '1998-12-16', '19855', 2019, 0, '0', '0', '3', '0102030405', NULL, NULL),
(5, 16673507, 3, 'Alexis', 'Le Fort', 'alexis.lenul@gmail.com', '6 Rue Perdue', NULL, '14546', 'PerduLand', 1, '1998-05-13', '19856', 2019, 0, '0', '0', '3', '0234657805', NULL, NULL);

-- --------------------------------------------------------

--
-- Structure de la table `usertitles`
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
-- Structure de la table `usertokens`
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
-- Déchargement des données de la table `usertokens`
--

INSERT INTO `usertokens` (`tokenId`, `userId`, `tokenType`, `tokenCreation`, `tokenExpiration`) VALUES
('65371119e0d9d63d4060df4a17b95be6db55da4e38d334d111ae81863cdad45f33106b68a6fe3ac7e15c81b18484a5da42e97fc69b3086bb163a83788f6986cd5f41a0d61a16a4d2dd9d8894b9564cb09a16b488aa641536b51c1e45520879f84186af88', 1, 'CONNECTION', '2018-10-16 19:51:18', '2018-10-16 21:03:07');

--
-- Contraintes pour les tables déchargées
--

--
-- Contraintes pour la table `logs`
--
ALTER TABLE `logs`
  ADD CONSTRAINT `fk_Log_users1` FOREIGN KEY (`userModified`) REFERENCES `users` (`userId`) ON DELETE NO ACTION,
  ADD CONSTRAINT `fk_Log_users2` FOREIGN KEY (`userAdmin`) REFERENCES `users` (`userId`) ON DELETE NO ACTION;

--
-- Contraintes pour la table `userauthentifications`
--
ALTER TABLE `userauthentifications`
  ADD CONSTRAINT `fk_userAuthentifications_users` FOREIGN KEY (`userId`) REFERENCES `users` (`userId`) ON DELETE NO ACTION;

--
-- Contraintes pour la table `usercredits`
--
ALTER TABLE `usercredits`
  ADD CONSTRAINT `fk_userCredit_users1` FOREIGN KEY (`userId`) REFERENCES `users` (`userId`) ON DELETE NO ACTION;

--
-- Contraintes pour la table `users`
--
ALTER TABLE `users`
  ADD CONSTRAINT `fk_users_categories1` FOREIGN KEY (`categoryId`) REFERENCES `categories` (`categoryId`) ON DELETE NO ACTION;

--
-- Contraintes pour la table `usertitles`
--
ALTER TABLE `usertitles`
  ADD CONSTRAINT `fk_userTitles_users1` FOREIGN KEY (`userId`) REFERENCES `users` (`userId`) ON DELETE NO ACTION;

--
-- Contraintes pour la table `usertokens`
--
ALTER TABLE `usertokens`
  ADD CONSTRAINT `fk_userTokens_users1` FOREIGN KEY (`userId`) REFERENCES `users` (`userId`) ON DELETE NO ACTION;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
