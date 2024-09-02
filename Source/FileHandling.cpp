#include "FileHandling.h"

namespace FileHandling
{
    void loadFile(const juce::File& file, juce::AudioFormatManager& formatManager, std::unique_ptr<juce::AudioFormatReaderSource>& readerSource, juce::AudioTransportSource& transportSource, juce::AudioThumbnail& thumbnail)
    {
        auto* reader = formatManager.createReaderFor(file);

        if (reader != nullptr)
        {
            std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
            transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
            readerSource.reset(newSource.release());

            thumbnail.setSource(new juce::FileInputSource(file));

            // Forza l'aggiornamento della thumbnail
            juce::MessageManager::callAsync([&thumbnail] { thumbnail.sendChangeMessage(); });
        }
        else
        {
            DBG("Errore nel caricamento del file: " + file.getFullPathName());
        }
    }

    void saveFile(const juce::File& file, juce::AudioFormatReader* reader, juce::Slider& volumeSlider)
    {
        if (reader == nullptr)
        {
            DBG("Error reading the source file");
            return;
        }

        juce::WavAudioFormat wavFormat;
        std::unique_ptr<juce::AudioFormatWriter> writer(wavFormat.createWriterFor(new juce::FileOutputStream(file),
            reader->sampleRate,
            reader->numChannels,
            16,
            {},
            0));

        if (writer == nullptr)
        {
            DBG("Error creating the writer");
            return;
        }

        juce::AudioBuffer<float> buffer(2, 8192);
        int64_t numSamples = reader->lengthInSamples;
        int64_t position = 0;

        while (position < numSamples)
        {
            int numSamplesToRead = (int)std::min<int64_t>(buffer.getNumSamples(), numSamples - position);
            reader->read(&buffer, 0, numSamplesToRead, position, true, true);
            buffer.applyGain((float)volumeSlider.getValue());

            writer->writeFromAudioSampleBuffer(buffer, 0, numSamplesToRead);
            position += numSamplesToRead;
        }

        DBG("File exported successfully: " + file.getFullPathName());
    }
}

