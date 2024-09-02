#include "UIComponents.h"

UIComponents::UIComponents(juce::Component& parent)
{
    // Inizializzazione componenti UI
    parent.addAndMakeVisible(importButton);
    importButton.setButtonText("Importa");

    parent.addAndMakeVisible(exportButton);
    exportButton.setButtonText("Esporta");

    parent.addAndMakeVisible(playButton);
    playButton.setButtonText("Play");
    playButton.setEnabled(true);

    parent.addAndMakeVisible(stopButton);
    stopButton.setButtonText("Stop");
    stopButton.setEnabled(false);

    parent.addAndMakeVisible(volumeSlider);
    volumeSlider.setRange(0.0, 1.0);
    volumeSlider.setValue(0.5);

    // Nuovi slider per la frequenza e l'ampiezza
    parent.addAndMakeVisible(frequencySlider);
    frequencySlider.setRange(20.0, 2000.0);
    frequencySlider.setValue(440.0);

    parent.addAndMakeVisible(amplitudeSlider);
    amplitudeSlider.setRange(0.0, 1.0);
    amplitudeSlider.setValue(0.5);

    // Nuova combobox per selezionare la sinusoide
    parent.addAndMakeVisible(waveTypeComboBox);
    waveTypeComboBox.addItem("Sine", 1);
    waveTypeComboBox.addItem("Square", 2);
    waveTypeComboBox.addItem("Triangle", 3);
    waveTypeComboBox.addItem("Sawtooth", 4);

    // Nuovo button per la modalità "Generatori di Toni"
    parent.addAndMakeVisible(toneGeneratorButton);
    toneGeneratorButton.setButtonText("Generatore di Toni");
}

UIComponents::~UIComponents()
{
    // Distruttore
}

void UIComponents::resizedComponents(juce::Component& parent)
{
    importButton.setBounds(10, 10, 100, 30);
    exportButton.setBounds(120, 10, 100, 30);
    playButton.setBounds(230, 10, 100, 30);
    stopButton.setBounds(340, 10, 100, 30);
    volumeSlider.setBounds(10, 50, parent.getWidth() - 20, 30);

    // Posiziona i nuovi slider
    frequencySlider.setBounds(10, 90, parent.getWidth() - 20, 30);
    amplitudeSlider.setBounds(10, 130, parent.getWidth() - 20, 30);

    // Posiziona la combobox e il button
    waveTypeComboBox.setBounds(10, 170, parent.getWidth() - 20, 30);
    toneGeneratorButton.setBounds(10, 210, parent.getWidth() - 20, 30);
}
