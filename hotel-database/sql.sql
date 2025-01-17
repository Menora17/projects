-- MySQL dump 10.13  Distrib 8.0.36, for Win64 (x86_64)
--
-- Host: localhost    Database: test
-- ------------------------------------------------------
-- Server version	8.3.0

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `employee`
--

DROP TABLE IF EXISTS `employee`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `employee` (
  `id` int NOT NULL,
  `name` varchar(255) DEFAULT NULL,
  `position` varchar(255) DEFAULT NULL,
  `contact_number` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UC_Employee_ContactNumber` (`contact_number`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employee`
--

LOCK TABLES `employee` WRITE;
/*!40000 ALTER TABLE `employee` DISABLE KEYS */;
INSERT INTO `employee` VALUES (1,'Michael Johnson','Housekeeper','555-1234'),(2,'Emily Brown','Front Desk Clerk','555-5678'),(3,'David Williams','Maintenance Technician','555-9876');
/*!40000 ALTER TABLE `employee` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `event`
--

DROP TABLE IF EXISTS `event`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `event` (
  `id` int NOT NULL,
  `name` varchar(255) DEFAULT NULL,
  `description` varchar(255) DEFAULT NULL,
  `start_date` date DEFAULT NULL,
  `end_date` date DEFAULT NULL,
  `facility_id` int DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_Event_Facility` (`facility_id`),
  CONSTRAINT `event_ibfk_1` FOREIGN KEY (`facility_id`) REFERENCES `facility` (`id`),
  CONSTRAINT `FK_Event_Facility` FOREIGN KEY (`facility_id`) REFERENCES `facility` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `event`
--

LOCK TABLES `event` WRITE;
/*!40000 ALTER TABLE `event` DISABLE KEYS */;
INSERT INTO `event` VALUES (1,'Pool Party','Summer kickoff party by the pool','2024-06-01','2024-06-01',1),(2,'Yoga Retreat','Weekend yoga retreat for relaxation','2024-07-15','2024-07-17',2),(3,'Fitness Bootcamp','Intensive fitness training program','2024-08-10','2024-08-12',3);
/*!40000 ALTER TABLE `event` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `facility`
--

DROP TABLE IF EXISTS `facility`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `facility` (
  `id` int NOT NULL,
  `name` varchar(255) DEFAULT NULL,
  `description` varchar(255) DEFAULT NULL,
  `status` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `facility`
--

LOCK TABLES `facility` WRITE;
/*!40000 ALTER TABLE `facility` DISABLE KEYS */;
INSERT INTO `facility` VALUES (1,'Swimming Pool','Outdoor pool area with sun loungers','operational'),(2,'Spa','Full-service spa offering massages and treatments','under maintenance'),(3,'Fitness Center','Fully equipped gym with cardio and weightlifting equipment','operational');
/*!40000 ALTER TABLE `facility` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `guest`
--

DROP TABLE IF EXISTS `guest`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `guest` (
  `id` int NOT NULL,
  `name` varchar(255) DEFAULT NULL,
  `contact_number` varchar(20) DEFAULT NULL,
  `email` varchar(255) DEFAULT NULL,
  `loyalty_program_id` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UC_Guest_Email` (`email`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `guest`
--

LOCK TABLES `guest` WRITE;
/*!40000 ALTER TABLE `guest` DISABLE KEYS */;
INSERT INTO `guest` VALUES (1,'John Smith','123456789','john@example.com','LOY001'),(2,'Jane Doe','987654321','jane@example.com','LOY002'),(3,'Michael Johnson','555555555','michael@example.com','LOY003');
/*!40000 ALTER TABLE `guest` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `housekeepinglog`
--

DROP TABLE IF EXISTS `housekeepinglog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `housekeepinglog` (
  `id` int NOT NULL,
  `room_id` int DEFAULT NULL,
  `employee_id` int DEFAULT NULL,
  `date` date DEFAULT NULL,
  `remarks` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_HousekeepingLog_Room` (`room_id`),
  KEY `FK_HousekeepingLog_Employee` (`employee_id`),
  CONSTRAINT `FK_HousekeepingLog_Employee` FOREIGN KEY (`employee_id`) REFERENCES `employee` (`id`),
  CONSTRAINT `FK_HousekeepingLog_Room` FOREIGN KEY (`room_id`) REFERENCES `room` (`id`),
  CONSTRAINT `housekeepinglog_ibfk_1` FOREIGN KEY (`room_id`) REFERENCES `room` (`id`),
  CONSTRAINT `housekeepinglog_ibfk_2` FOREIGN KEY (`employee_id`) REFERENCES `employee` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `housekeepinglog`
--

LOCK TABLES `housekeepinglog` WRITE;
/*!40000 ALTER TABLE `housekeepinglog` DISABLE KEYS */;
INSERT INTO `housekeepinglog` VALUES (1,1,1,'2024-03-20','Room cleaned and tidied up'),(2,2,2,'2024-03-21','Bedding changed and room vacuumed'),(3,3,3,'2024-05-10','Repaired broken lamp');
/*!40000 ALTER TABLE `housekeepinglog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `maintenancerequest`
--

DROP TABLE IF EXISTS `maintenancerequest`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `maintenancerequest` (
  `id` int NOT NULL,
  `room_id` int DEFAULT NULL,
  `issue` varchar(255) DEFAULT NULL,
  `status` varchar(50) DEFAULT NULL,
  `date_reported` date DEFAULT NULL,
  `date_resolved` date DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `room_id` (`room_id`),
  CONSTRAINT `maintenancerequest_ibfk_1` FOREIGN KEY (`room_id`) REFERENCES `room` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `maintenancerequest`
--

LOCK TABLES `maintenancerequest` WRITE;
/*!40000 ALTER TABLE `maintenancerequest` DISABLE KEYS */;
INSERT INTO `maintenancerequest` VALUES (1,1,'Broken lamp','reported','2024-03-22',NULL),(2,2,'Leaky faucet','resolved','2024-03-23','2024-03-24'),(3,3,'Faulty air conditioning','reported','2024-05-11',NULL);
/*!40000 ALTER TABLE `maintenancerequest` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `payment`
--

DROP TABLE IF EXISTS `payment`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `payment` (
  `id` int NOT NULL,
  `reservation_id` int DEFAULT NULL,
  `amount` float DEFAULT NULL,
  `method` varchar(50) DEFAULT NULL,
  `status` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_Payment_Reservation` (`reservation_id`),
  CONSTRAINT `FK_Payment_Reservation` FOREIGN KEY (`reservation_id`) REFERENCES `reservation` (`id`),
  CONSTRAINT `payment_ibfk_1` FOREIGN KEY (`reservation_id`) REFERENCES `reservation` (`id`),
  CONSTRAINT `CHK_Payment_Amount` CHECK ((`amount` >= 0))
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `payment`
--

LOCK TABLES `payment` WRITE;
/*!40000 ALTER TABLE `payment` DISABLE KEYS */;
INSERT INTO `payment` VALUES (1,1,350,'credit card','paid'),(2,2,220,'cash','pending'),(3,3,500,'credit card','pending');
/*!40000 ALTER TABLE `payment` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `after_payment_insert` AFTER INSERT ON `payment` FOR EACH ROW BEGIN
    UPDATE Guest
    SET loyalty_program_id = NEW.reservation_id
    WHERE id = (SELECT guest_id FROM Reservation WHERE id = NEW.reservation_id);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `reservation`
--

DROP TABLE IF EXISTS `reservation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `reservation` (
  `id` int NOT NULL,
  `guest_id` int DEFAULT NULL,
  `room_id` int DEFAULT NULL,
  `check_in_date` date DEFAULT NULL,
  `check_out_date` date DEFAULT NULL,
  `number_of_guests` int DEFAULT NULL,
  `status` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_Reservation_Guest` (`guest_id`),
  KEY `FK_Reservation_Room` (`room_id`),
  CONSTRAINT `FK_Reservation_Guest` FOREIGN KEY (`guest_id`) REFERENCES `guest` (`id`),
  CONSTRAINT `FK_Reservation_Room` FOREIGN KEY (`room_id`) REFERENCES `room` (`id`),
  CONSTRAINT `reservation_ibfk_1` FOREIGN KEY (`guest_id`) REFERENCES `guest` (`id`),
  CONSTRAINT `reservation_ibfk_2` FOREIGN KEY (`room_id`) REFERENCES `room` (`id`),
  CONSTRAINT `CHK_Reservation_Dates` CHECK ((`check_out_date` > `check_in_date`))
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reservation`
--

LOCK TABLES `reservation` WRITE;
/*!40000 ALTER TABLE `reservation` DISABLE KEYS */;
INSERT INTO `reservation` VALUES (1,1,1,'2024-03-20','2024-03-25',2,'confirmed'),(2,2,2,'2024-04-01','2024-04-05',1,'confirmed'),(3,3,3,'2024-05-10','2024-05-15',2,'confirmed');
/*!40000 ALTER TABLE `reservation` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `after_reservation_insert` AFTER INSERT ON `reservation` FOR EACH ROW BEGIN
    UPDATE Room
    SET status = 'occupied'
    WHERE id = NEW.room_id;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `reservationservice`
--

DROP TABLE IF EXISTS `reservationservice`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `reservationservice` (
  `reservation_id` int NOT NULL,
  `service_id` int NOT NULL,
  PRIMARY KEY (`reservation_id`,`service_id`),
  KEY `service_id` (`service_id`),
  CONSTRAINT `reservationservice_ibfk_1` FOREIGN KEY (`reservation_id`) REFERENCES `reservation` (`id`),
  CONSTRAINT `reservationservice_ibfk_2` FOREIGN KEY (`service_id`) REFERENCES `service` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reservationservice`
--

LOCK TABLES `reservationservice` WRITE;
/*!40000 ALTER TABLE `reservationservice` DISABLE KEYS */;
INSERT INTO `reservationservice` VALUES (1,1),(1,2),(2,2),(3,3);
/*!40000 ALTER TABLE `reservationservice` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `room`
--

DROP TABLE IF EXISTS `room`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `room` (
  `id` int NOT NULL,
  `number` varchar(50) DEFAULT NULL,
  `type` varchar(50) DEFAULT NULL,
  `status` varchar(50) DEFAULT NULL,
  `price_per_night` float DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UC_Room_Number` (`number`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `room`
--

LOCK TABLES `room` WRITE;
/*!40000 ALTER TABLE `room` DISABLE KEYS */;
INSERT INTO `room` VALUES (1,'101','Standard','available',100),(2,'102','Deluxe','available',150),(3,'103','Suite','available',200);
/*!40000 ALTER TABLE `room` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `roomserviceassignment`
--

DROP TABLE IF EXISTS `roomserviceassignment`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `roomserviceassignment` (
  `room_id` int NOT NULL,
  `employee_id` int NOT NULL,
  `assignment_date` date DEFAULT NULL,
  PRIMARY KEY (`room_id`,`employee_id`),
  KEY `FK_RoomServiceAssignment_Employee` (`employee_id`),
  CONSTRAINT `FK_RoomServiceAssignment_Employee` FOREIGN KEY (`employee_id`) REFERENCES `employee` (`id`),
  CONSTRAINT `FK_RoomServiceAssignment_Room` FOREIGN KEY (`room_id`) REFERENCES `room` (`id`),
  CONSTRAINT `roomserviceassignment_ibfk_1` FOREIGN KEY (`room_id`) REFERENCES `room` (`id`),
  CONSTRAINT `roomserviceassignment_ibfk_2` FOREIGN KEY (`employee_id`) REFERENCES `employee` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `roomserviceassignment`
--

LOCK TABLES `roomserviceassignment` WRITE;
/*!40000 ALTER TABLE `roomserviceassignment` DISABLE KEYS */;
INSERT INTO `roomserviceassignment` VALUES (1,1,'2024-03-20'),(2,2,'2024-03-21'),(3,3,'2024-05-10');
/*!40000 ALTER TABLE `roomserviceassignment` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `service`
--

DROP TABLE IF EXISTS `service`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `service` (
  `id` int NOT NULL,
  `name` varchar(255) DEFAULT NULL,
  `description` varchar(255) DEFAULT NULL,
  `price` float DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `service`
--

LOCK TABLES `service` WRITE;
/*!40000 ALTER TABLE `service` DISABLE KEYS */;
INSERT INTO `service` VALUES (1,'Breakfast','Full American Breakfast',15),(2,'Room Cleaning','Daily room cleaning service',20),(3,'Airport Shuttle','Transportation to and from the airport',25);
/*!40000 ALTER TABLE `service` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'test'
--

--
-- Dumping routines for database 'test'
--
/*!50003 DROP FUNCTION IF EXISTS `CalculateAverageServicePrice` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` FUNCTION `CalculateAverageServicePrice`() RETURNS float
    READS SQL DATA
BEGIN
    DECLARE avg_price FLOAT;
    
    SELECT AVG(price)
    INTO avg_price
    FROM Service;
    
    RETURN avg_price;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP FUNCTION IF EXISTS `CalculateRoomPriceByType` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` FUNCTION `CalculateRoomPriceByType`(room_type VARCHAR(50)) RETURNS float
    READS SQL DATA
BEGIN
    DECLARE room_price FLOAT;
    
    SELECT price_per_night
    INTO room_price
    FROM Room
    WHERE type = room_type;
    
    RETURN room_price;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-04-03 19:02:41
