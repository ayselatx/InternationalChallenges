// Récupère les éléments nécessaires
const progressBar = document.getElementById('progressBar');
const progressValue = document.getElementById('progressValue');
const temperatureRange = document.getElementById('temperatureRange');

// Fonction pour mettre à jour la barre de progression et la valeur
function updateProgress() {
  const value = temperatureRange.value; // Récupère la valeur du slider
  progressBar.style.width = value + '%'; // Modifie la largeur de la barre de progression
  progressValue.textContent = value + '%'; // Affiche la valeur à côté de la barre
}

// Appelle la fonction au changement de valeur du slider
temperatureRange.addEventListener('input', updateProgress);

// Initialisation au chargement de la page
updateProgress();
;