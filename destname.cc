// This file is part of Extract PDFmark.
//
// Copyright (C) 2016 Masamichi Hosoda
//
// Extract PDFmark is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Foobar is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Extract PDFmark.  If not, see <http://www.gnu.org/licenses/>.

#include "config.h"

#include <iostream>
#include <PDFDoc.h>
#include <Link.h>

#include "destname.hh"
#include "destname-private.hh"

void put_destname (PDFDoc *doc, GooString *name)
{
  LinkDest *link_dest = doc->findDest (name);
  if (link_dest)
    {
      int pagenum;
      if (link_dest->isPageRef ())
        {
          Ref page_ref = link_dest->getPageRef ();
          pagenum = doc->findPage (page_ref.num, page_ref.gen);
        }
      else
        {
          pagenum = link_dest->getPageNum ();
        }

      switch (link_dest->getKind ())
        {
        case destXYZ:
          std::cout
            << "[ /Dest (" << name->getCString ()
            << ") /Page " << pagenum
            << " /View [/XYZ " << link_dest->getLeft ()
            << " " << link_dest->getTop ()
            << " " << link_dest->getZoom ()
            << "] /DEST pdfmark" << std::endl;
          break;
        default:
          std::cout << "%  link_dest kind is unknown." << std::endl;
          break;
        }

      delete link_dest;
    }
  else
    {
      std::cout << "%  link_dest is null." << std::endl;
    }
}

void put_destnametree (PDFDoc *doc)
{
  Catalog *catalog = doc->getCatalog ();
  if (catalog && catalog->isOk ())
    {
      NameTree *destnametree = get_destnametree (catalog);
      if (destnametree)
        {
          int len = destnametree->numEntries ();
          for (int i=0; i<len; ++i)
            {
              put_destname (doc, destnametree->getName (i));
            }
        }
      else
        {
          std::cout << "% NameTree is null" << std::endl;
        }
    }
  else
    std::cout << "% Catalog is not OK" << std::endl;
}