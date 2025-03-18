#include <AESlib.h>

AESLib aesLib;

// Clé AES de 16 octets (128 bits)
const byte aesKey[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                         0xab, 0xf7, 0x97, 0x75, 0x46, 0x1d, 0x6f, 0x6f};

// Données à chiffrer (doivent être multiples de 16 octets)
byte inputData[16] = {'T', 'e', 's', 't', ' ', 'D', 'a', 't', 'a', ' ', 'f', 'o', 'r', ' ', 'A', 'E'};

// Tableau pour les données chiffrées
byte outputData[16];

void setup()
{
    Serial.begin(115200);

    // Afficher les données avant chiffrement
    Serial.println("Données avant chiffrement:");
    for (int i = 0; i < 16; i++)
    {
        Serial.print((char)inputData[i]);
    }
    Serial.println();

    // Chiffrement des données
    aesLib.encrypt(inputData, outputData, aesKey);

    // Afficher les données chiffrées
    Serial.println("Données après chiffrement:");
    for (int i = 0; i < 16; i++)
    {
        Serial.print(outputData[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    // Déchiffrement des données
    byte decryptedData[16]; // Tableau pour stocker les données déchiffrées
    aesLib.decrypt(outputData, decryptedData, aesKey);

    // Afficher les données après déchiffrement
    Serial.println("Données après déchiffrement:");
    for (int i = 0; i < 16; i++)
    {
        Serial.print((char)decryptedData[i]);
    }
    Serial.println();
}

void loop()
{
    // Pas besoin de faire quoi que ce soit dans le loop, tout se fait dans setup()
}
