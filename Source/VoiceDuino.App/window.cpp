#include "window.h"
#include "ui_window.h"

Window::Window(QWidget* parent) : QMainWindow(parent), ui(new Ui::Window)
{
    ui->setupUi(this);

    direction = 0;
    value = 0;

    connect(ui->buttonAudio, SIGNAL(released()), SLOT(OnExplore()));
    connect(ui->buttonLang, SIGNAL(released()), SLOT(OnExplore()));
    connect(ui->buttonDict, SIGNAL(released()), SLOT(OnExplore()));
    connect(ui->buttonInitialize, SIGNAL(released()), SLOT(OnInitialize()));
    connect(ui->buttonDestroy, SIGNAL(released()), SLOT(OnDestroy()));
    connect(ui->buttonStart, SIGNAL(released()), SLOT(OnRecognite()));
    connect(ui->comboDevices, SIGNAL(currentIndexChanged(int)), SLOT(OnDeviceChanged()));
    connect(&initWatcher, SIGNAL(finished()), SLOT(OnInitialized()));
    connect(&recognizeWatcher, SIGNAL(finished()), SLOT(OnRecognized()));

    readSettings();
}

Window::~Window()
{
    delete ui;
}

void Window::OnExplore()
{
    QObject* sender = QObject::sender();
    QFileDialog fileDialog(this);

    if(sender == ui->buttonAudio)
    {
        fileDialog.setFileMode(QFileDialog::Directory);
        fileDialog.setOption(QFileDialog::ShowDirsOnly);

        if(fileDialog.exec() == QFileDialog::Accepted)
        {
            QStringList selected = fileDialog.selectedFiles();
            if(!selected.isEmpty()) ui->editAudio->setText(selected.first());
        }
    }
    else
    {
        if(fileDialog.exec() == QFileDialog::Accepted)
        {
            QStringList selected = fileDialog.selectedFiles();
            if(!selected.isEmpty())
            {
                if(sender == ui->buttonLang) ui->editLang->setText(selected.first());
                else if(sender == ui->buttonDict) ui->editDict->setText(selected.first());
            }
        }
    }
}

void Window::OnDestroy()
{
    recognition.Destroy();
    ui->buttonStart->setEnabled(false);
    ui->buttonDestroy->setEnabled(false);
    ui->buttonInitialize->setEnabled(true);
}

void Window::OnRecognite()
{
    if(!recognition.IsInitialized()) return;

    ui->buttonDestroy->setEnabled(false);
    ui->buttonStart->setEnabled(false);
    ui->labelIcon->setPixmap(QPixmap(":/root/Resources/record.ico"));

    QFuture<QString> future = QtConcurrent::run(&recognition, &Recognition::Recognize);
    recognizeWatcher.setFuture(future);
}

void Window::OnRecognized()
{
    QString data = recognizeWatcher.result();
    if(!data.isEmpty())
    {
        ui->editText->appendPlainText(data);

        if (data.mid(0,5) == "робот")
        {
            QString word_data = data.mid(6,4);

            if (word_data == "впер")
            {
                ui->labelUp->setEnabled(true);
                ui->labelDown->setEnabled(false);
                ui->labelLeft->setEnabled(false);
                ui->labelRight->setEnabled(false);
                ui->labelStop->setEnabled(false);

                value = (quint32)str2num.string2number(data.mid(13));
                ui->labelUpValue->setText(QString::number(value));
                ui->labelDownValue->clear();
                ui->labelLeftValue->clear();
                ui->labelRightValue->clear();

                direction = 0x01;
            }
            else if (word_data == "наза")
            {
                ui->labelUp->setEnabled(false);
                ui->labelDown->setEnabled(true);
                ui->labelLeft->setEnabled(false);
                ui->labelRight->setEnabled(false);
                ui->labelStop->setEnabled(false);

                value = (quint32)str2num.string2number(data.mid(12));
                ui->labelUpValue->clear();
                ui->labelDownValue->setText(QString::number(value));
                ui->labelLeftValue->clear();
                ui->labelRightValue->clear();

                direction = 0x02;
            }
            else if (word_data == "нале")
            {
                ui->labelUp->setEnabled(false);
                ui->labelDown->setEnabled(false);
                ui->labelLeft->setEnabled(true);
                ui->labelRight->setEnabled(false);
                ui->labelStop->setEnabled(false);

                value = (quint32)str2num.string2number(data.mid(13));
                ui->labelUpValue->clear();
                ui->labelDownValue->clear();
                ui->labelLeftValue->setText(QString::number(value));
                ui->labelRightValue->clear();

                direction = 0x03;
            }
            else if (word_data == "напр")
            {
                ui->labelUp->setEnabled(false);
                ui->labelDown->setEnabled(false);
                ui->labelLeft->setEnabled(false);
                ui->labelRight->setEnabled(true);
                ui->labelStop->setEnabled(false);

                value = (quint32)str2num.string2number(data.mid(14));
                ui->labelUpValue->clear();
                ui->labelDownValue->clear();
                ui->labelLeftValue->clear();
                ui->labelRightValue->setText(QString::number(value));

                direction = 0x04;
            }
            else if (word_data == "стоп")
            {
                ui->labelUp->setEnabled(false);
                ui->labelDown->setEnabled(false);
                ui->labelLeft->setEnabled(false);
                ui->labelRight->setEnabled(false);
                ui->labelStop->setEnabled(true);

                ui->labelUpValue->clear();
                ui->labelDownValue->clear();
                ui->labelLeftValue->clear();
                ui->labelRightValue->clear();

                direction = 0x05;
                value = 0x00000000;
            }
            else
            {
                ui->labelUp->setEnabled(false);
                ui->labelDown->setEnabled(false);
                ui->labelLeft->setEnabled(false);
                ui->labelRight->setEnabled(false);
                ui->labelStop->setEnabled(false);

                ui->labelUpValue->clear();
                ui->labelDownValue->clear();
                ui->labelLeftValue->clear();
                ui->labelRightValue->clear();

                direction = 0x00;
                value = 0x00000000;
            }
        }
        else
        {
            ui->labelUp->setEnabled(false);
            ui->labelDown->setEnabled(false);
            ui->labelLeft->setEnabled(false);
            ui->labelRight->setEnabled(false);
            ui->labelStop->setEnabled(false);

            ui->labelUpValue->clear();
            ui->labelDownValue->clear();
            ui->labelLeftValue->clear();
            ui->labelRightValue->clear();

            direction = 0x00;
            value = 0x00000000;
        }

        QByteArray datagram;
        QDataStream out(&datagram, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_7);
        quint16 STX = 0xA0A1;
        quint8 SIZE = 0x0A;
        quint8 DIR = direction;
        quint32 VAL = value;
        quint16 ETX = 0xA1A0;
        out << STX << SIZE << DIR << VAL << ETX;
        out.device()->seek(0);
        udpSocket.writeDatagram(datagram.data(), datagram.size(), QHostAddress("192.168.240.1") , 4321);
    }

    ui->buttonDestroy->setEnabled(true);
    ui->buttonStart->setEnabled(true);
    ui->labelIcon->setPixmap(QPixmap(":/root/Resources/norecord.ico"));
}

void Window::OnInitialize()
{
    QString audioModel = ui->editAudio->text();
    QString langModel = ui->editLang->text();
    QString dictionary = ui->editDict->text();
    QString device = ui->comboDevices->currentText();
    int sampleRate = ui->comboRates->currentText().toInt();

    if(audioModel.isEmpty() || langModel.isEmpty() ||
       dictionary.isEmpty() || device.isEmpty() || sampleRate <= 0)
        QMessageBox::critical(this, tr("Ошибка"), tr("Необходимо заполнить все поля!"));
    else
    {
        QFuture<bool> future = QtConcurrent::run(&recognition,
            &Recognition::Initialize, audioModel, langModel, dictionary, device, sampleRate);
        initWatcher.setFuture(future);
    }
}

void Window::OnInitialized()
{
    if(!initWatcher.result())
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось инициализировать распознавание!"));
    else
    {
        ui->buttonInitialize->setEnabled(false);
        ui->buttonDestroy->setEnabled(true);
        ui->buttonStart->setEnabled(true);
    }
}

void Window::OnDeviceChanged()
{
    int currentIndex = ui->comboDevices->currentIndex();
    if(currentIndex < 0) return;

    QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    QAudioDeviceInfo device = devices.at(currentIndex);
    QList<int> rates = device.supportedSampleRates();
    QStringList ratesStr;
    foreach (int rate, rates)
        ratesStr.append(QString::number(rate));

    ui->comboRates->clear();
    ui->comboRates->addItems(ratesStr);
}

void Window::enumMicrophones(int index)
{
    QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    foreach (QAudioDeviceInfo device, devices)
    {
        if(device.isNull()) continue;
        QString deviceName = device.deviceName();
        ui->comboDevices->addItem(deviceName);
    }

    if(index < ui->comboDevices->count())
        ui->comboDevices->setCurrentIndex(index);
}

void Window::readSettings()
{
    QSettings settings("VoiceDuino");
    settings.beginGroup("General");

    int deviceIndex = settings.value("device").toInt();
    int rateIndex = settings.value("rate").toInt();

    enumMicrophones(deviceIndex);
    OnDeviceChanged();

    if(rateIndex < ui->comboRates->count())
        ui->comboRates->setCurrentIndex(rateIndex);

    ui->editAudio->setText(settings.value("audio").toString());
    ui->editLang->setText(settings.value("lang").toString());
    ui->editDict->setText(settings.value("dict").toString());
    restoreState(settings.value("state").toByteArray());
    restoreGeometry(settings.value("geometry").toByteArray());

    settings.endGroup();
}

void Window::writeSettings()
{
    QSettings settings("VoiceDuino");
    settings.beginGroup("General");

    settings.setValue("device", ui->comboDevices->currentIndex());
    settings.setValue("rate", ui->comboRates->currentIndex());
    settings.setValue("audio", ui->editAudio->text());
    settings.setValue("lang", ui->editLang->text());
    settings.setValue("dict", ui->editDict->text());
    settings.setValue("state", saveState());
    settings.setValue("geometry", saveGeometry());

    settings.endGroup();
}

void Window::closeEvent(QCloseEvent* event)
{
    writeSettings();
    event->accept();
}
