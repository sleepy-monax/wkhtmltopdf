#pragma once

// Copyright 2010-2020 wkhtmltopdf authors
// Copyright 2023-2024 Odoo S.A.
//
// This file is part of wkhtmltopdf.
//
// wkhtmltopdf is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// wkhtmltopdf is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with wkhtmltopdf.  If not, see <http://www.gnu.org/licenses/>.

#include "converter.hh"
#include "pdfsettings.hh"

namespace wkhtmltopdf {

class PdfConverterPrivate;

class PdfConverter : public Converter {
	Q_OBJECT
  public:
	PdfConverter(settings::PdfGlobal & globalSettings);
	~PdfConverter();
	int pageCount();
	void addResource(const settings::PdfObject & pageSettings, const QString * data = 0);
	const settings::PdfGlobal & globalSettings() const;
	const QByteArray & output();
	static const qreal millimeterToPointMultiplier;

  private:
	PdfConverterPrivate * d;
	virtual ConverterPrivate & priv();
	friend class PdfConverterPrivate;
  signals:
	void producingForms(bool);
};

} // namespace wkhtmltopdf
