#define DELAI_CLIGNOTEMENT 100
#define DELAI_TOUCHE 150 // Supérieur à 100

// Nombre de boutons
const uint8_t NBR_BOUTONS = 6;

// Indiquer sur quelles broches sont connectés les boutons
uint8_t pins[NBR_BOUTONS] = {D1, D2, D3, D5, D6, D7};

// Au démarrage, on assume que les boutons sont relâchés
uint8_t state[NBR_BOUTONS] = {LOW};
  
// Fonction exécutée au démarrage
void setup() {
  // Configurrer les broches des boutons en mode "Entrée"
  for (uint8_t i = 0; i < NBR_BOUTONS ; i++) {
    pinMode(pins[i], INPUT);
  }

  // Configurer la broche de la DEL en mode "Sortie"
  pinMode(BUILTIN_LED, OUTPUT);

  // Faire clignoter la DEL 3 fois rapidement au démarrage
  for (uint8_t i = 0; i < 3 ; i++) {

    // Allumer et attendre
    digitalWrite(BUILTIN_LED, LOW);
    delay(DELAI_CLIGNOTEMENT);

    // Éteindre et attendre
    digitalWrite(BUILTIN_LED, HIGH);
    delay(DELAI_CLIGNOTEMENT);

  } // Recommencer le clignotement de la DEL, ou continuer s'il y a déjà eu 3 clignotements

  // Configurer la vitesse de communication avec l'ordinateur
  Serial.begin(115200);

  // Envoyer un message à l'ordinateur
  Serial.println("Manette");
}

// Fonction exécutée en boucle à l'infini
void loop() {

  // Pour chacun des boutons...
  for (uint8_t i = 0; i < NBR_BOUTONS ; i++) {

    // Lire l'état du bouton (haut ou bas)
    uint8_t etat_pin = !digitalRead(pins[i]);

    // Si l'état est haut
    if (etat_pin == HIGH) {

      // Envoyer le numéro du bouton à l'ordinateur
      Serial.print(i);

      // Allumer la DEL
      digitalWrite(BUILTIN_LED, LOW);

    }

  } // Recommencer le traitement du prochain bouton, ou continuer si on a traité le dernier bouton

  // Attendre un peu
  delay(100);

  // Éteindre la DEL
  digitalWrite(BUILTIN_LED, HIGH);

  // Attendre encore un peu
  delay(DELAI_TOUCHE-100);
}
