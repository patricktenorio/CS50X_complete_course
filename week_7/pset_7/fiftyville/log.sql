-- Keep a log of any SQL queries you execute as you solve the mystery.
-----------------------------------------------------------------------------------------------------------------------

-- You may find it helpful to start with the crime_scene_reports table.
SELECT * FROM crime_scene_reports;

-----------------------------------------------------------------------------------------------------------------------

-- The theft took place on July 28, 2021 and that it took place on Humphrey Street.
SELECT * FROM crime_scene_reports WHERE month=7 AND day=28 AND year=2021 AND street='Humphrey Street';

-- INVESTIGATION REPORT:
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Inerviews were conducted today with three witnesses who were present at the time.
-- Each of their interview transcripts mentions the (bakery).

-----------------------------------------------------------------------------------------------------------------------

-- Checked all bakery security logs as per the previous investigation report
SELECT * FROM bakery_security_logs;

-----------------------------------------------------------------------------------------------------------------------

-- Checked security logs dated July 28, 2021 at 10pm - 11pm
SELECT * FROM bakery_security_logs WHERE month=7 AND day=28 AND year=2021 AND hour=10;

-- Can't determine. Need more investigation. Next to check interviews

-----------------------------------------------------------------------------------------------------------------------

-- Checked all interviews dated July 28, 2021. As per the previous reports, there were 3 witnesses
SELECT * FROM interviews WHERE month=7 AND day=28 AND year=2021;

-- Witness #1: Ruth - Sometime within (ten minutes) of the theft, I saw the thief get into a car in the bakery parking
-- lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that
-- left the partking lot in that time frame.

-- Witness #2: Eugene - I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I
-- arrived at Emma's bakery, I was walking by the (ATM on Leggett Street) and saw the thief where withdrawing some moeny.

-- Witness #3: Raymond - As the thief was leaving the bakery, they called someone who (talked to them for less than a
-- minute.) In the call, I heard the thief say that they were planning to take the (earliest flight out of Fiftyville
-- tomorrow.) The thief then asked the person on the other end of the phone to (purchase the flight ticket).

-----------------------------------------------------------------------------------------------------------------------

-- Checked at_transactions as per witness #2 - Ruth (checked dated July 28, 2021)
SELECT * FROM atm_transactions WHERE month=7 AND day=28 AND year=2021;

-- Also filtered atm_location (Leggett Street) and transaction_type (withdraw)
SELECT * FROM atm_transactions WHERE month=7 AND day=28 AND year=2021
AND atm_location='Leggett Street' AND transaction_type='withdraw';

-- Account Numbers and withdraw amount results
-- 28500762 | 48
-- 28296815 | 20
-- 76054385 | 60
-- 49610011 | 50
-- 16153065 | 80
-- 25506511 | 20
-- 81061156 | 30
-- 26013199 | 35

-----------------------------------------------------------------------------------------------------------------------

-- Checked eached bank accounts above to see if there's a match

-- person id and creation date = 46700 | 2014
SELECT * FROM bank_accounts WHERE account_number=28500762;

-- person id and creation date = 395717 | 2014
SELECT * FROM bank_accounts WHERE account_number=28500762;

-- person id and creation date = 449774 | 2015
SELECT * FROM bank_accounts WHERE account_number=76054385;

-- person id and creation date = 686048 | 2010
SELECT * FROM bank_accounts WHERE account_number=49610011;

-- person id and creation date = 458378 | 2012
SELECT * FROM bank_accounts WHERE account_number=16153065;

-- person id and creation date = 396669 | 2014
SELECT * FROM bank_accounts WHERE account_number=25506511;

-- person id and creation date = 438727 | 2018
SELECT * FROM bank_accounts WHERE account_number=81061156;

-- person id and creation date = 514354 | 2012
SELECT * FROM bank_accounts WHERE account_number=26013199;

-----------------------------------------------------------------------------------------------------------------------

-- As per witness #3 - Raymond - they call and talked for less than a minute
-- Checked phone calls that day with phoen calls duration less than a minute
SELECT * FROM phone_calls WHERE month=7 AND day=28 AND year=2021 AND duration < 60;

-- Caller | Receiver | Duration
-- (130) 555-0289 | (996) 555-8899 | 51
-- (499) 555-9472 | (892) 555-8872 | 36
-- (367) 555-5533 | (375) 555-8161 | 45
-- (499) 555-9472 | (717) 555-1342 | 50
-- (286) 555-6063 | (676) 555-6554 | 43
-- (770) 555-1861 | (725) 555-3243 | 49
-- (031) 555-6622 | (910) 555-3251 | 38
-- (826) 555-1652 | (066) 555-9701 | 55
-- (338) 555-6650 | (704) 555-2131 | 54

-----------------------------------------------------------------------------------------------------------------------

-- Also as per witness #3, the thief were planning to take the earliest flight out of Fiftyville tomorrow
-- Checked flights table details for some clue
SELECT * FROM flights;

-- Checked for July 29 earliest flights since witness said earliest flight tomorrow
SELECT * FROM flights WHERE day=29 ORDER BY hour;

-- 2 morning flights schedule for July 29
-- origin airport id | destination airport id | sched
-- 8 | 4 | 8:20am
-- 8 | 1 | 9:30am

-- Checked Airports table and saw Fiftyville Regional Airport
SELECT * FROM airports;

-- abbr | airport name | city
-- CSF | Fiftyville Regional Airport | Fiftyville

-----------------------------------------------------------------------------------------------------------------------

-- The thief then asked the person on the other end of the phone to (purchase the flight ticket).

-- Tried checking the passenger list
SELECT * FROM passengers;

-- But still need mroe clue

-----------------------------------------------------------------------------------------------------------------------

-- As per witness #3, the thief then asked the person on the other end of the phone to (purchase the flight ticket)
-- Checked the people table and cross checked the phone numbers results we got above
SELECT * FROM people;

-- Checked RECEIVERS number
-- name | phone number | passport_number | license palte

-- (130) 555-0289 | (996) 555-8899 | 51
-- CALLER: Sofia | (130) 555-0289 | 1695452385 | G412CB7
-- RECEIVER: Jack | (996) 555-8899 | 9029462229 | 52R0Y8U
SELECT * FROM people WHERE phone_number='(130) 555-0289';
SELECT * FROM people WHERE phone_number='(996) 555-8899';

-- (499) 555-9472 | (892) 555-8872 | 36
-- CALLER: Kelsey | (499) 555-9472 | 8294398571 | 0NTHK55
-- RECEIVER: Larry | (892) 555-8872 | 2312901747 | O268ZZ0
SELECT * FROM people WHERE phone_number='(499) 555-9472';
SELECT * FROM people WHERE phone_number='(892) 555-8872';

-- (367) 555-5533 | (375) 555-8161 | 45
-- CALLER: Bruce | (367) 555-5533 | 5773159633 | 94KL13X
-- RECEIVER: Robin | (375) 555-8161 | N/A | 4V16VO0
SELECT * FROM people WHERE phone_number='(367) 555-5533';
SELECT * FROM people WHERE phone_number='(375) 555-8161';

-- (499) 555-9472 | (717) 555-1342 | 50
-- CALLER: Kelsey | (499) 555-9472 | 8294398571 | 0NTHK55
-- RECEIVER: Melissa | (717) 555-1342 | 7834357192 | N/A
SELECT * FROM people WHERE phone_number='(499) 555-9472';
SELECT * FROM people WHERE phone_number='(717) 555-1342';

-- (286) 555-6063 | (676) 555-6554 | 43
-- CALELR: Taylor | (286) 555-6063 | 1988161715 | 1106N58
-- RECEIVER: James | (676) 555-6554 | 2438825627 | Q13SVG6
SELECT * FROM people WHERE phone_number='(286) 555-6063';
SELECT * FROM people WHERE phone_number='(676) 555-6554';

-- (770) 555-1861 | (725) 555-3243 | 49
-- CALLER: Diana | (770) 555-1861 | 3592750733 | 322W7JE
-- RECEIVER: Philip | (725) 555-3243 | 3391710505 | GW362R6
SELECT * FROM people WHERE phone_number='(770) 555-1861';
SELECT * FROM people WHERE phone_number='(725) 555-3243';

-- (031) 555-6622 | (910) 555-3251 | 38
-- CALLER: Carina | (031) 555-6622 | 9628244268 | Q12B3Z3
-- RECEIVER: Jacqueline | (910) 555-3251 | N/A | 43V0R5D
SELECT * FROM people WHERE phone_number='(031) 555-6622';
SELECT * FROM people WHERE phone_number='(910) 555-3251';

-- (826) 555-1652 | (066) 555-9701 | 55
-- CALLER: Kenny | (826) 555-1652 | 9878712108 | 30G67EN
-- RECEIVER: Doris | (066) 555-9701 | 7214083635 | M51FA04
SELECT * FROM people WHERE phone_number='(826) 555-1652';
SELECT * FROM people WHERE phone_number='(066) 555-9701';

-- (338) 555-6650 | (704) 555-2131 | 54
-- CALLER: Benista | (338) 555-6650 | 9586786673 | 8X428L0
-- RECEIVER: Anna | (704) 555-2131 | N/A | N/A
SELECT * FROM people WHERE phone_number='(338) 555-6650';
SELECT * FROM people WHERE phone_number='(704) 555-2131';

-----------------------------------------------------------------------------------------------------------------------

-- Cross check callers license plate to bakery parking cctv during the said time


-- CALLERS LICENSE PLATES:
-- CALLER: Sofia | (130) 555-0289 | 1695452385 | G412CB7
-- CALLER: Kelsey | (499) 555-9472 | 8294398571 | 0NTHK55
-- CALLER: Bruce | (367) 555-5533 | 5773159633 | 94KL13X
-- CALELR: Taylor | (286) 555-6063 | 1988161715 | 1106N58
-- CALLER: Diana | (770) 555-1861 | 3592750733 | 322W7JE
-- CALLER: Carina | (031) 555-6622 | 9628244268 | Q12B3Z3
-- CALLER: Kenny | (826) 555-1652 | 9878712108 | 30G67EN
-- CALLER: Benista | (338) 555-6650 | 9586786673 | 8X428L0

-- BAKERY PARKED CARS DURING THE SAID TIME:
SELECT * FROM bakery_security_logs WHERE month=7 AND day=28 AND year=2021 AND hour=10;
-- entrance | R3G7486
-- entrance | 13FNH73
-- exit     | 5P2BI95
-- exit     | 94KL13X
-- exit     | 6P58WS2
-- exit     | 4328GD8
-- exit     | G412CB7
-- exit     | L93JTIZ
-- exit     | 322W7JE
-- exit     | 0NTHK55
-- exit     | 1106N58
-- entrance | NRYN856
-- entrance | WD5M8I6
-- entrance | V47T75I

-- MATCHED LICENSE PLATE:
-- G412CB7 - exit
-- 0NTHK55 - exit
-- 94KL13X - exit
-- 1106N58 - exit
-- 322W7JE - exit

-----------------------------------------------------------------------------------------------------------------------

-- Checked people table to match license plates

-- G412CB7
SELECT * FROM people WHERE license_plate='G412CB7';
-- Sofia | (130) 555-0289 | 1695452385 | G412CB7

-- 0NTHK55
SELECT * FROM people WHERE license_plate='0NTHK55';
-- Kelsey | (499) 555-9472 | 8294398571 | 0NTHK55

-- 94KL13X
SELECT * FROM people WHERE license_plate='94KL13X';
-- Bruce | (367) 555-5533 | 5773159633 | 94KL13X

-- 1106N58
SELECT * FROM people WHERE license_plate='1106N58';
-- Taylor | (286) 555-6063 | 1988161715 | 1106N58

-- 322W7JE
SELECT * FROM people WHERE license_plate='322W7JE';
-- Diana | (770) 555-1861 | 3592750733 | 322W7JE

-----------------------------------------------------------------------------------------------------------------------

-- Checked passengers table to cross check passport number
SELECT * FROM passengers;

-- flight id | passport number | seat number

-- Sofia | (130) 555-0289 | 1695452385 | G412CB7
SELECT * FROM passengers WHERE passport_number=1695452385;
-- 36 | 1695452385 | 3B

-- Kelsey | (499) 555-9472 | 8294398571 | 0NTHK55
SELECT * FROM passengers WHERE passport_number=8294398571;
-- 36 | 8294398571 | 6C

-- Bruce | (367) 555-5533 | 5773159633 | 94KL13X
SELECT * FROM passengers WHERE passport_number=5773159633;
-- 36 | 5773159633 | 4A

-- Taylor | (286) 555-6063 | 1988161715 | 1106N58
SELECT * FROM passengers WHERE passport_number=1988161715;
-- 36 | 1988161715 | 6D

-- Diana | (770) 555-1861 | 3592750733 | 322W7JE
SELECT * FROM passengers WHERE passport_number=3592750733;
-- 18 | 3592750733 | 4C
-- 24 | 3592750733 | 2C
-- 54 | 3592750733 | 6C

-----------------------------------------------------------------------------------------------------------------------

-- Checked again atm transactions
SELECT * FROM atm_transactions WHERE month=7 AND day=28 AND year=2021
AND atm_location='Leggett Street' AND transaction_type='withdraw';

-- Cross check to bank accounts:
-- Account Numbers and withdraw amount results:

-- 28500762 | 48
SELECT * FROM bank_accounts WHERE account_number=28500762;
-- person id: 467400 | 2014

-- 28296815 | 20
SELECT * FROM bank_accounts WHERE account_number=28296815;
-- person id: 395717 | 2014

-- 76054385 | 60
SELECT * FROM bank_accounts WHERE account_number=76054385;
-- person id: 449774 | 2015

-- 49610011 | 50
SELECT * FROM bank_accounts WHERE account_number=49610011;
-- person id: 686048 | 2010

-- 16153065 | 80
SELECT * FROM bank_accounts WHERE account_number=16153065;
-- person id: 458378 | 2012

-- 25506511 | 20
SELECT * FROM bank_accounts WHERE account_number=25506511;
-- person id: 396669 | 2014

-- 81061156 | 30
SELECT * FROM bank_accounts WHERE account_number=81061156;
-- person id: 438727 | 2018

-- 26013199 | 35
SELECT * FROM bank_accounts WHERE account_number=26013199;
-- person id: 514354 | 2012

-----------------------------------------------------------------------------------------------------------------------

-- Checked flight details to see origin and destination:
SELECT * FROM flights WHERE day=29 ORDER BY hour;
-- Checked again bakery security logs to cross check license plates
SELECT * FROM bakery_security_logs WHERE month=7 AND day=28 AND year=2021 AND hour=10 AND minute > 15 AND activity='exit';

-- SUSPECTS:

-- Name: Sofia
-- Person ID: 398010
-- License Plate: G412CB7
-- Phone Number:(130) 555-0289
-- Passport Number: 1695452385
-- Bakery Pariking: In parking within 10mins exiting

-- Name: Kelsey
-- Person ID: 560886
-- License Plate: 0NTHK55
-- Phone Number: (499) 555-9472
-- Passport Number: 8294398571
-- Bakery Pariking: In parking within 10mins exiting

-- Name: Bruce
-- Person ID: 686048
-- License Plate: 94KL13X
-- Phone Number: (367) 555-5533
-- Passport Number: 5773159633
-- Bakery Pariking: In parking within 10mins exiting
-----------------------------------------------------------------------------------------------------------------------

-- Theft of the CS50 duck SQL Mystery (final answer)

-- THIEF DETAILS:
-- Name: Bruce
-- Person ID: 686048
-- License Plate: 94KL13X
-- Phone Number: (367) 555-5533
-- Passport Number: 5773159633
-- Bakery Pariking: In parking within 10mins exiting
-- Withdraw ATM Location: Leggett Street (matched bank id)
-- ACCOMPLICE: Robin (receiver of the call)

-- Flight Seat Details:
-- Origin Airport: 8 | CSF | Fiftyville Regional Airport | Fiftyville (earliest flight)
-- Destination Airport: 4 | LGA | LaGuardia Airport | New York City

