
function updateTemperature(value) {
  const progressBar = document.getElementById("progressBarTemperature");
  let value2 = 20 + value/2
  progressBar.style.width = value2 + "%";
  let element = document.getElementById("infoTemperature");  
  element.dataset.valeur = value + "°C";
  element.textContent = element.dataset.valeur; // to show value on progressbar
}

function updateHumidity(value) {
  const progressBar = document.getElementById("progressBarHumidity");
  progressBar.style.width = value + "%";
  let element = document.getElementById("infoHumidity");  
  element.dataset.valeur = value + "%";
  element.textContent = element.dataset.valeur; // to show value on progressbar
}

function updatePressure(value) {
  const progressBar = document.getElementById("progressBarPressure");
  let value2 =(value)/20
  progressBar.style.width = value2 + "%";
  let element = document.getElementById("infoPressure");  
  element.dataset.valeur = value + "hPa";  
  element.textContent = element.dataset.valeur; // to show value on progressbar
}


function startProgress() {
  let progress = 0;
  const interval = setInterval(() => {
      if (progress >= 100) {
          clearInterval(interval); // Stop l'animation à 100%
      } else {
          progress += 1; // Augmente de 10% à chaque itération
          updateProgress(progress);
      }
  }, 500); // Met à jour toutes les 500ms (0.5s)
}



function updateProgress(value) {
  let progressBar = document.getElementById("progressBarTemperature");
  let overlay = document.getElementById("progressOverlayTemperature");

  let percentage = (value / 50) * 100;  // Assuming max temp is 50°
  progressBar.style.width = "100%";    // Gradient always fills the bar
  overlay.style.width = (100 - percentage) + "%"; // Covers unused area
}

// Example: Call this function with a value (e.g., 25°)
document.addEventListener("DOMContentLoaded", function () {
  updateProgress(25);
});
