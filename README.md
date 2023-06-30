# Digitalni merač vremena

Ovaj projekat predstavlja digitalni merač intervala vremena koji koristi Arduino za merenje vremena u satima, minutima, sekundama i milisekundama. Uredjaj se koristi za mjerenje intervala vremena vremenskih releja (Direktnih ili indirektnih). Pomocu ovog uredjaja mozete precizno podesiti vremenski relej na odredjeno vreme odrade.

## Komponente

- Arduino UNO, ili Arduino Nano
- LCD ekran sa I2C konverterom
- Taster za start/stop merenja vremena
- Taster za resetovanje merenja vremena
- Taster za promenu stanja releja preko kog se startuje vremenski relej
- Relej
- LED diode za indikaciju stanja releja
- Potrebni otpornici i žice

## Biblioteke

- LiquidCrystal_I2C: biblioteka za upravljanje LCD ekranom preko I2C komunikacije
- EEPROM: biblioteka za rad sa EEPROM memorijom

## Uputstvo za korišćenje

1. Povežite Arduino i ostale komponente prema shemi povezivanja.
2. Učitajte kod na Arduino.
3. Pokrenite Arduino.
4. Na LCD ekranu će se prikazati početna poruka "POKRENI MJERENJE NA START".
5. Pritisnite taster za start merenja kako biste započeli merenje vremena. Relej će se uključiti/isključiti u zavisnosti od poslednjeg stanja.
6. Pritisnite taster za stop merenja kako biste zaustavili merenje vremena. Relej će se takođe promeniti u suprotno stanje.
7. Pritisnite taster za reset merenja kako biste resetovali merenje vremena i vratili se na početno stanje.
8. Pritisnite taster za promenu stanja releja kako biste promenili stanje releja u zavisnosti da li mjerite vrijeme odrade direktnog ili inverznog vremenskog releja.

## Autor

Projekat je razvijen od strane Radenko Bogdanovic. Za sva pitanja ili sugestije, možete me kontaktirati na [e-pošta].

## Licenca

Licencu za koristenje možete pronaći u [fajlu sa licencom](https://github.com/rasho/DMIN/blob/main/Licence.md).

