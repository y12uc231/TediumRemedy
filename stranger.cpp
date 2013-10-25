#include "stranger.h"
#include <QDebug>
#include <QJsonDocument>

Stranger::Stranger(QObject *parent) :
    QObject(parent)
{
    nam = new QNetworkAccessManager(this);
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(urlRequestFinished(QNetworkReply*)));
}

void Stranger::StartConversation() {
    QUrl requestUrl("http://front2.omegle.com/start?rcs=1&firstevents=1&spid=&randid=MG6PZ6ZP&lang=en");
    const QNetworkRequest request(requestUrl);
    const QByteArray data;
    QNetworkReply *reply = nam->post(request, data);
}


void Stranger::SendMessage(QString *messageText) {

}

void Stranger::StartTyping() {

}

void Stranger::StopTyping() {

}

void Stranger::urlRequestFinished(QNetworkReply *reply) {
    QByteArray replyData = reply->readAll();
    QString replyText(replyData);
    qDebug() << replyText;

    QJsonParseError parseError;
    QJsonDocument jDocument = QJsonDocument::fromJson(replyData, &parceError);
    QJsonObject jObject = jDocument.object();

    jObject.value("");

    delete reply;

    pollNewEvents(); //if stranger not disconnected
}

void Stranger::pollNewEvents() {
    QUrl requestUrl("http://front2.omegle.com/events");
    const QNetworkRequest request(requestUrl);
    const QByteArray data = QString("id=" + QUrl::toPercentEncoding(clientID));
    QNetworkReply *reply = nam->post(request, data);
}