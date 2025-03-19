#include "DHT11.h"
#include "AESlib.h"

AESLib aesLib;

// Clé AES de 16 octets (128 bits)
const byte aesKey[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                         0xab, 0xf7, 0x97, 0x75, 0x46, 0x1d, 0x6f, 0x6f};

// Taille des données à chiffrer (température + humidité)
const int dataSize = 2; // Température et humidité (2 octets)

DHT11::DHT11(int pin) : _pin(pin)
{
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH);
}

// Fonction pour chiffrer la température et l'humidité
int DHT11::encryptData(int temperature, int humidity, byte encryptedData[16])
{
    /*byte data[2] = {(byte)humidity, (byte)temperature}; // Humidité et température sous forme d'octets*/

    // Créer un tableau de 16 octets pour contenir les données
    byte data[16] = {0}; // Remplir tout le tableau avec des zéros

    // Placer l'humidité (1 octet) et la température (1 octet) dans le tableau
    data[0] = (byte)humidity;
    data[1] = (byte)temperature;

    aesLib.encrypt(data, encryptedData, aesKey); // Chiffre les 2 octets
    return 0;                                    // Indiquer que le chiffrement a réussi
}

// Fonction pour déchiffrer les données chiffrées
int DHT11::decryptData(byte encryptedData[16], int &temperature, int &humidity)
{
    byte decryptedData[16];

    aesLib.decrypt(encryptedData, decryptedData, aesKey); // Déchiffre les données

    // Récupère l'humidité et la température à partir des données déchiffrées
    humidity = decryptedData[0];
    temperature = decryptedData[1];

    return 0; // Indiquer que le déchiffrement a réussi
}

/**
 * Lit la température et l'humidité, puis les chiffre.
 */
int DHT11::readEncryptedTemperatureHumidity(int &temperature, int &humidity)
{
    byte data[5];
    int error = readRawData(data);
    if (error != 0)
    {
        return error;
    }

    // Température et humidité lues du capteur
    humidity = data[0];
    temperature = data[2];

    // Chiffrement des données (température et humidité)
    byte encryptedData[16]; // 16 octets pour les données chiffrées
    encryptData(temperature, humidity, encryptedData);

    // Optionnel : afficher les données chiffrées en hexadécimal (pour le débogage)
    Serial.println("Données chiffrées :");
    for (int i = 0; i < 16; i++)
    {
        Serial.print(encryptedData[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    // Déchiffrement des données pour récupérer les valeurs originales
    decryptData(encryptedData, temperature, humidity);

    return 0; // Indiquer que tout s'est bien passé
}
