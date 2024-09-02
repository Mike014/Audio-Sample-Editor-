#include "MainComponent.h"
#include "FileHandling.h"
#include "AudioProcessing.h"
#include "UIComponents.h"

MainComponent::MainComponent()
    : thumbnailCache(5), thumbnail(32, formatManager, thumbnailCache), state(Stopped), uiComponents(*this) // Aumenta il numero di campioni per pixel
{
    // Inizializzazione componenti UI
    uiComponents.importButton.addListener(this);
    uiComponents.exportButton.addListener(this);
    uiComponents.playButton.addListener(this);
    uiComponents.stopButton.addListener(this);
    uiComponents.volumeSlider.addListener(this);

    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);

    // Inizializzazione del AudioDeviceManager
    setAudioChannels(0, 2);

    setSize(800, 600);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
    transportSource.removeChangeListener(this);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    transportSource.getNextAudioBlock(bufferToFill);

    // Proteggi il buffer audio
    for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
    {
        AudioProcessing::applyAdvancedSmoothing(*bufferToFill.buffer, bufferToFill.numSamples);
    }
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::releaseResources()
{
    transportSource.releaseResources();
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);

    // Disegna la thumbnail
    auto thumbnailBounds = getLocalBounds().reduced(10);
    if (thumbnail.getTotalLength() > 0.0)
    {
        thumbnail.drawChannels(g, thumbnailBounds, 0.0, thumbnail.getTotalLength(), 1.0f);
    }
    else
    {
        g.setFont(20.0f);
        g.drawFittedText("No file loaded", thumbnailBounds, juce::Justification::centred, 1);
    }
}

void MainComponent::resized()
{
    uiComponents.resizedComponents(*this);

    // Ridisegna la thumbnail
    repaint();
}

void MainComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        if (transportSource.isPlaying())
        {
            changeState(Playing);
        }
        else
        {
            if (state == Stopping)
                changeState(Stopped);
            else
                changeState(Stopped); // Assicurati che lo stato venga aggiornato correttamente
        }
    }
}

void MainComponent::buttonClicked(juce::Button* clickedButton)
{
    if (clickedButton == &uiComponents.importButton)
    {
        DBG("Import button clicked");
        auto chooser = std::make_shared<juce::FileChooser>("Seleziona un file audio da importare...", juce::File{}, "*.wav;*.mp3;*.aiff");
        chooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this, chooser](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file.exists())
                {
                    DBG("File selected: " + file.getFullPathName());
                    FileHandling::loadFile(file, formatManager, readerSource, transportSource, thumbnail);
                    repaint();
                }
                else
                {
                    DBG("No file selected");
                }
            });
    }
    else if (clickedButton == &uiComponents.exportButton)
    {
        DBG("Export button clicked");
        auto chooser = std::make_shared<juce::FileChooser>("Salva il file audio...", juce::File{}, "*.wav");
        chooser->launchAsync(juce::FileBrowserComponent::saveMode | juce::FileBrowserComponent::canSelectFiles,
            [this, chooser](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file != juce::File{})
                {
                    DBG("File selected for saving: " + file.getFullPathName());
                    FileHandling::saveFile(file, readerSource->getAudioFormatReader(), uiComponents.volumeSlider);
                }
                else
                {
                    DBG("No file selected for saving");
                }
            });
    }
    else if (clickedButton == &uiComponents.playButton)
    {
        DBG("Play button clicked");
        changeState(Starting);
    }
    else if (clickedButton == &uiComponents.stopButton)
    {
        DBG("Stop button clicked");
        changeState(Stopping);
    }
}


void MainComponent::changeState(TransportState newState)
{
    if (state != newState)
    {
        state = newState;

        switch (state)
        {
        case Stopped:
            uiComponents.playButton.setEnabled(true);
            uiComponents.stopButton.setEnabled(false);
            transportSource.setPosition(0.0);
            break;

        case Starting:
            transportSource.setPosition(0.0); // Reimposta la posizione all'inizio del file
            transportSource.start();
            break;

        case Playing:
            uiComponents.playButton.setEnabled(false);
            uiComponents.stopButton.setEnabled(true);
            break;

        case Stopping:
            transportSource.stop();
            break;
        }
    }
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &uiComponents.volumeSlider)
    {
        DBG("Volume slider value changed: " + juce::String(slider->getValue()));
        transportSource.setGain((float)slider->getValue());
        repaint();
    }
}

// MainComponent.cpp
void MainComponent::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &uiComponents.waveTypeComboBox)
    {
        int selectedId = comboBoxThatHasChanged->getSelectedId();
        DBG("ComboBox changed: " + juce::String(selectedId));

        // Implementa la logica per gestire i cambiamenti della ComboBox
        switch (selectedId)
        {
        case 1:
            DBG("Sine wave selected");
            // Logica per la sinusoide
            break;
        case 2:
            DBG("Square wave selected");
            // Logica per l'onda quadra
            break;
        case 3:
            DBG("Triangle wave selected");
            // Logica per l'onda triangolare
            break;
        case 4:
            DBG("Sawtooth wave selected");
            // Logica per l'onda a dente di sega
            break;
        default:
            DBG("Unknown wave type selected");
            break;
        }
    }
}



























