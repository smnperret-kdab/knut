/*
  This file is part of Knut.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "imageview.h"
#include "core/imagedocument.h"
#include "guisettings.h"

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QShortcut>
#include <QWheelEvent>

namespace Gui {

ImageView::ImageView(QWidget *parent)
    : QGraphicsView(parent)
{
    setScene(new QGraphicsScene(this));

    auto zoomReset = new QShortcut(QKeySequence("Ctrl+0"), this);
    zoomReset->setContext(Qt::WidgetShortcut);
    connect(zoomReset, &QShortcut::activated, this, [this]() {
        setTransform({});
    });

    auto zoomIn = new QAction(tr("Zoom in"), this);
    GuiSettings::setIcon(zoomIn, ":/gui/magnify-plus.png");
    zoomIn->setShortcut(QKeySequence("Ctrl++"));
    zoomIn->setShortcutContext(Qt::WidgetShortcut);
    connect(zoomIn, &QAction::triggered, this, [this]() {
        scale(2, 2);
    });
    addAction(zoomIn);

    auto zoomOut = new QAction(tr("Zoom out"), this);
    GuiSettings::setIcon(zoomOut, ":/gui/magnify-minus.png");
    zoomOut->setShortcut(QKeySequence("Ctrl+-"));
    zoomOut->setShortcutContext(Qt::WidgetShortcut);
    connect(zoomOut, &QAction::triggered, this, [this]() {
        scale(.5, .5);
    });
    addAction(zoomOut);
}

void ImageView::setImageDocument(Core::ImageDocument *document)
{
    scene()->addPixmap(QPixmap::fromImage(document->image()));
}

void ImageView::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
        scale(2, 2);
    else
        scale(.5, .5);

    QGraphicsView::wheelEvent(event);
}

void ImageView::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect)
    painter->resetTransform();
    painter->fillRect(0, 0, width(), height(), QBrush(QImage(":/gui/tile.png")));
}

} // namespace Gui
