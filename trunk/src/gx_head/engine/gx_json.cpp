
/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * ---------------------------------------------------------------------------
 *
 *    This is the gx_head system interface
 *
 * ----------------------------------------------------------------------------
 */

#include "engine.h"               // NOLINT

#include <sys/stat.h>

namespace gx_system {

/****************************************************************
 ** JsonWriter
 */

JsonWriter::JsonWriter(ostream *o)
    : os(o),
      first(true),
      deferred_nl(false),
      indent("") {}

JsonWriter::~JsonWriter() {
    close();
}

void JsonWriter::close() {
    if (is_closed()) {
	return;
    }
    if (deferred_nl) {
	*os << endl;
    }
    os = 0;
}

inline void JsonWriter::komma() {
    if (first)
        first = false;
    else if (!deferred_nl)
        *os << ", ";
    else
        *os << ",";
    flush();
}

inline void JsonWriter::space() {
    if (first)
        first = false;
    else if (!deferred_nl)
        *os << " ";
    flush();
}

inline void JsonWriter::iplus() {
    indent += "  ";
}

inline void JsonWriter::iminus() {
    if (!indent.empty()) {
        indent = indent.substr(0, indent.size() - 2);
    }
}

void JsonWriter::write(float v, bool nl) {
    komma();
    *os << v;
    snl(nl);
}

void JsonWriter::write(double v, bool nl) {
    komma();
    *os << v;
    snl(nl);
}

void JsonWriter::write(int i, bool nl) {
    komma();
    *os << i;
    snl(nl);
}

void JsonWriter::write(unsigned int i, bool nl) {
    komma();
    *os << i;
    snl(nl);
}

void JsonWriter::write_lit(const string& s, bool nl) {
    komma();
    *os << s;
    snl(nl);
}

void JsonWriter::write(const char* p, bool nl) {
    komma();
    *os << '"';
    while (*p) {
        switch (*p) {
        case '\\': case '"': *os << '\\'; break;
        case '\b': *os << '\\'; *os << 'b'; continue;       // NOLINT
        case '\f': *os << '\\'; *os << 'f'; continue;       // NOLINT
        case '\n': *os << '\\'; *os << 'n'; continue;       // NOLINT
        case '\r': *os << '\\'; *os << 'r'; continue;       // NOLINT
        case '\t': *os << '\\'; *os << 't'; continue;       // NOLINT
        }
        *os << *p++;
    }
    *os << '"';
    snl(nl);
}

void JsonWriter::begin_object(bool nl) {
    komma();
    *os << '{';
    snl(nl);
    first = true;
    iplus();
}

void JsonWriter::end_object(bool nl) {
    iminus();
    flush();
    first = false;
    *os << '}';
    snl(nl);
}

void JsonWriter::begin_array(bool nl) {
    komma();
    *os << '[';
    snl(nl);
    first = true;
    iplus();
}

void JsonWriter::end_array(bool nl) {
    iminus();
    flush();
    first = false;
    *os << ']';
    snl(nl);
}

void JsonWriter::write_key(const char* p, bool nl) {
    write(p, nl);
    *os << ": ";
    first = true;
}

void JsonWriter::write_key(const string& p, bool nl) {
    write(p, nl);
    *os << ": ";
    first = true;
}

// called before output of next element
void JsonWriter::flush() {
    if (deferred_nl) {
        *os << endl;
        deferred_nl = false;
        *os << indent;
    }
}


/****************************************************************
 ** JsonParser
 */

const char* JsonParser::token_names[] = {
    "no_token", "end_token", "begin_object", "end_object",
    "begin_array", "end_array", "value_string", "value_number",
    "value_key" };

JsonException::JsonException(const char* desc) {
    what_str = string("Json parse error: ") + desc;
}

JsonParser::JsonParser(istream* i)
    : is(i),
    depth(0),
    cur_tok(no_token),
    nl(false),
    next_depth(0),
    next_tok(no_token) {}

JsonParser::~JsonParser() {
    close();
}

void JsonParser::close() {
    if (is_closed()) {
	return;
    }
    is = 0;
}

void JsonParser::throw_unexpected(token expect) {
    ostringstream b;
    b << "unexpected token: " << token_names[cur_tok]
      << " (expected: " << token_names[expect] << ")"
      << endl;
    throw JsonException(b.str().c_str());
}

const char* unicode2utf8(unsigned int input) {
    const int maskbits   = 0x3F;
    const int maskbyte   = 0x80;
    const int mask2bytes = 0xC0;
    const int mask3bytes = 0xE0;
    static char result[4];
    int n = 0;
    // 0xxxxxxx
    if (input < 0x80) {
        result[n++] = static_cast<char>(input);

    // 110xxxxx 10xxxxxx
    } else if (input < 0x800) {
        result[n++] = (static_cast<char>(mask2bytes | (input >> 6)));
        result[n++] = (static_cast<char>(maskbyte | (input & maskbits)));

    // 1110xxxx 10xxxxxx 10xxxxxx
    } else {
        result[n++] = (static_cast<char>(mask3bytes | (input >> 12)));
        result[n++] = (static_cast<char>(maskbyte | ((input >> 6) & maskbits)));
        result[n++] = (static_cast<char>(maskbyte | (input & maskbits)));
    }
    result[n++] = '\0';
    return result;
}

const char* JsonParser::readcode() {
    int code = 0;
    for (int i = 0; i < 4; i++) {
        int n = is->get();
        if (!is->good())
            throw JsonException("eof");
        if ('0' <= n && n <= '9')
            n = n - '0';
        else
            n = 10 + (toupper(n) - 'A');
        code = code * 16 + n;
    }
    return unicode2utf8(code);
}

string JsonParser::readstring() {
    ostringstream os("");
    char c;
    do {
        is->get(c);
        if (!is->good())
            return "";
        if (c == '\\') {
            is->get(c);
            if (!is->good())
                return "";
            switch (c) {
            case 'b': os << '\b'; break;
            case 'f': os << '\f'; break;
            case 'n': os << '\n'; break;
            case 'r': os << '\r'; break;
            case 't': os << '\t'; break;
	    case '"': os << '"'; break;
            case 'u': os << readcode(); break;
            default: is->get(c); os << c; break;
            }
        } else if (c == '"') {
            return os.str();
        } else {
            os << c;
        }
    } while (true);
}

string JsonParser::readnumber(char c) {
    ostringstream os("");
    do {
        os << c;
        c = is->peek();
        switch (c) {
        case '+': case '-': case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': case 'e': case 'E':
        case '.':
            break;
        default:
            return os.str();
        }
        is->get(c);
    } while (is->good());
    return "";
}

void JsonParser::read_next() {
    if (next_tok == end_token)
        return;
    if (next_tok != no_token and next_depth == 0) {
        next_tok = end_token;
        return;
    }
    char c;
    nl = false;
    while (true) {
        do {
            is->get(c);
            if (!is->good())
                throw JsonException("eof");
            if (c == '\n')
                nl = true;
        } while (c == ' ' || c == '\t' || c == '\r' || c == '\n');
	next_pos = is->tellg();
        switch (c) {
        case '[': next_tok = begin_array; next_depth++; break;

        case ']': next_tok = end_array; next_depth--; break;

        case '{': next_tok = begin_object; next_depth++; break;

        case '}': next_tok = end_object; next_depth--; break;

        case ',': continue;

        case '"':
            next_str = readstring();
            *is >> c;
            if (!is->good())
                throw JsonException("eof");
            if (c == ':') {
                next_tok = value_key;
            } else {
                is->unget();
                next_tok = value_string;
            }
            break;

        case '-': case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            next_str = readnumber(c);
            next_tok = value_number;
            break;

        default:
            throw JsonException("bad token");
        }
        break;
    }
}

JsonParser::token JsonParser::next(token expect) {
    if (cur_tok != end_token) {
        if (next_tok == no_token)
            read_next();
        depth = next_depth;
        cur_tok = next_tok;
        str = next_str;
        if (next_tok != end_token)
            read_next();
    }
    if (expect != no_token)
        check_expect(expect);
    return cur_tok;
}


void JsonParser::copy_object(JsonWriter& jw) {
    int curdepth = depth;
    do {
        switch (next()) {
        case begin_object:
            jw.begin_object(nl);
            break;
        case end_object:
            jw.end_object(nl);
            break;
        case begin_array:
            jw.begin_array(nl);
            break;
        case end_array:
            jw.end_array(nl);
            break;
        case value_string:
            jw.write(current_value(), nl);
            break;
        case value_number:
            jw.write_lit(current_value(), nl);
            break;
        case value_key:
            jw.write_key(current_value().c_str(), nl);
            break;
        default:
            throw JsonException("unexpected token");
        }
    } while (curdepth != depth);
}

void JsonParser::skip_object() {
    int curdepth = depth;
    do {
        if (next() == end_token) {
            throw JsonException("unexpected eof");
        }
    } while (curdepth != depth);
}


/****************************************************************
 ** class SettingsFileHeader
 */

const string SettingsFileHeader::gx_version = GX_VERSION;

void SettingsFileHeader::read(JsonParser& jp) {
    jp.next(JsonParser::value_string);
    if (jp.current_value() != "gx_head_file_version") {
        throw JsonException("invalid gx_head file header");
    }
    jp.next(JsonParser::begin_array);
    jp.next(JsonParser::value_number);
    file_major = jp.current_value_int();
    jp.next(JsonParser::value_number);
    file_minor = jp.current_value_int();
    jp.next(JsonParser::value_string);
    file_gx_version = jp.current_value();
    jp.next(JsonParser::end_array);
}

void SettingsFileHeader::write(JsonWriter& jw) {
    jw.write("gx_head_file_version");
    jw.begin_array();
    jw.write(major); // major format version
    jw.write(minor); // minor format version
    jw.write(gx_version);
    jw.end_array(true);
}

void SettingsFileHeader::write_major_minor_version(JsonWriter& jw, int majv, int minv) {
    jw.begin_array();
    jw.write(majv);
    jw.write(minv);
    jw.end_array();
}

void SettingsFileHeader::read_major_minor_version(JsonParser& jp) {
    jp.next(JsonParser::begin_array);
    jp.next(JsonParser::value_number);
    file_major = jp.current_value_int();
    jp.next(JsonParser::value_number);
    file_minor = jp.current_value_int();
    jp.next(JsonParser::end_array);
}

bool SettingsFileHeader::make_empty_settingsfile(const string& name) {
    ofstream os(name.c_str());
    if (!os.good()) {
	return false;
    }
    JsonWriter jw(&os);
    jw.begin_array();
    SettingsFileHeader::write(jw);
    jw.end_array(true);
    jw.close();
    os.close();
    return true;
}


/****************************************************************
 ** class StateFile
 */

class JsonReader: public JsonParser {
public:
    JsonReader(istream* is) : JsonParser(is) {}
    ~JsonReader();
    void close();
};

JsonReader::~JsonReader() {
    close();
}

void JsonReader::close() {
    if (is_closed()) {
	return;
    }
    next(JsonParser::end_array);
    next(JsonParser::end_token);
    JsonParser::close();
}

JsonParser *StateFile::create_reader() {
    if (is) {
	is->seekg(0);
    } else {
	struct stat st;
	if (stat(filename.c_str(), &st) == 0) {
	    mtime = st.st_mtime;
	} else {
	    mtime = 0;
	}
	is = new ifstream(filename.c_str());
    }
    JsonReader *jp = new JsonReader(is);
    jp->next(JsonParser::begin_array);
    header.read(*jp);
    if (header.is_major_diff()) {
	if (header.get_major() == 0) {
	    gx_print_info(_("recall settings"), _("loading converted state"));
	} else {
	    gx_print_warning(
		_("recall settings"),
		boost::format(_("major version mismatch in %1%: found %2%, expected %3%"))
		% filename % header.get_major() % static_cast<int>(SettingsFileHeader::major));
	}
    }
    return jp;
}

void StateFile::ensure_is_current() {
    if (filename.empty() || !mtime) {
	return;
    }
    struct stat st;
    if (stat(filename.c_str(), &st) == 0) {
	if (st.st_mtime == mtime) {
	    return;
	}
    } else {
	mtime = 0;
    }
    delete is;
    is = 0;
}


class ModifyState: public JsonWriter {
private:
    string filename;
    string tmpfile;
    ofstream os;
public:
    ModifyState(const string& name);
    ~ModifyState();
    virtual void close();
};

ModifyState::ModifyState(const string& name)
    : filename(name),
      tmpfile(filename + "_tmp"),
      os(tmpfile.c_str()) {
    set_stream(&os);
    begin_array();
    SettingsFileHeader::write(*this);
}

ModifyState::~ModifyState() {
    close();
}

void ModifyState::close() {
    if (is_closed()) {
	return;
    }
    end_array(true);
    JsonWriter::close();
    os.close();
    if (!os.good()) {
	gx_print_error(_("save preset"),
		       boost::format(_("couldn't write %1%")) % tmpfile);
    } else {
	int rc = rename(tmpfile.c_str(), filename.c_str());
	if (rc != 0) {
	    gx_print_error(_("save preset"),
			   boost::format(_("couldn't rename %1% to %2%"))
			   % tmpfile % filename);
	}
    }
}

class ModifyStatePreservePreset: public ModifyState {
private:
    ifstream is;
    JsonParser jp;
public:
    ModifyStatePreservePreset(const string& name, bool *preserve_preset);
    ~ModifyStatePreservePreset();
};

ModifyStatePreservePreset::ModifyStatePreservePreset(const string& name, bool *preserve_preset)
    : ModifyState(name),
      is(name.c_str()),
      jp(&is) {
    bool copied = false;
    if (is.good()) {
	try {
	    jp.next(JsonParser::begin_array);
	    SettingsFileHeader header;
	    header.read(jp);
	    while (jp.peek() != JsonParser::end_array) {
		jp.next(JsonParser::value_string);
		if (jp.current_value() == "current_preset") {
		    write(jp.current_value());
		    jp.copy_object(*this);
		    copied = true;
		} else {
		    jp.skip_object();
		}
	    }
	} catch(JsonException& e) {
	    // just ignore
	}
    }
    if (!copied) {
	*preserve_preset = false;
    }
}

ModifyStatePreservePreset::~ModifyStatePreservePreset() {
}

JsonWriter *StateFile::create_writer(bool *preserve_preset) {
    JsonWriter *jw;
    if (*preserve_preset) {
	jw = new ModifyStatePreservePreset(filename, preserve_preset);
    } else {
	jw = new ModifyState(filename);
    }
    delete is;
    is = 0;
    return jw;
}


/****************************************************************
 ** class PresetFile
 */

PresetFile::PresetFile()
    : filename(),
      is(0),
      mtime(),
      header(),
      entries(),
      name(),
      tp(),
      flags() {
}

PresetFile::PresetFile(const Glib::ustring& name_, const std::string& path, int tp_, int flags_, SettingsFileHeader header_, time_t mtime_)
    : filename(path),
      is(0),
      mtime(mtime_),
      header(header_),
      entries(),
      name(name_),
      tp(tp_),
      flags(flags_) {
}

void PresetFile::open() {
    delete is;
    is = 0;
    entries.clear();
    if (filename.empty()) {
	return;
    }
    struct stat st;
    if (stat(filename.c_str(), &st) == 0) {
	mtime = st.st_mtime;
    } else {
	mtime = 0;
    }
    is = new ifstream(filename.c_str());
    JsonParser jp(is);
    jp.next(JsonParser::begin_array);
    header.read(jp);
    while (jp.peek() == JsonParser::value_string) {
	jp.next();
	if (jp.current_value() == "midi_controller") { //FIXME there should be a file signature
	    if (jp.peek() == JsonParser::begin_array) {
		entries.clear();
		is->setstate(istream::failbit);
		gx_print_error(
		    _("open preset"),
		    boost::format(_("%1% is a state file, not a preset file")) % filename);
		throw JsonException(_("This is a state file, not a preset file"));
	    }
	}
	streampos pos = jp.get_streampos();
	entries.push_back(Position(jp.current_value(), pos));
	jp.skip_object();
    }
    jp.next(JsonParser::end_array);
    jp.next(JsonParser::end_token);
}

void PresetFile::ensure_is_current() {
    if (filename.empty() || !mtime) {
	return;
    }
    struct stat st;
    if (stat(filename.c_str(), &st) == 0) {
	if (st.st_mtime == mtime) {
	    return;
	}
    } else {
	mtime = 0;
    }
    delete is;
    is = 0;
}

void PresetFile::open(const std::string& fname) {
    filename = fname;
    open();
}

const SettingsFileHeader& PresetFile::get_header() {
    reopen();
    return header;
}

void PresetFile::fill_names(vector<Glib::ustring>& l) {
    reopen();
    for (vector<Position>::const_iterator i = entries.begin(); i != entries.end(); ++i) {
	l.push_back(i->name);
    }
}

Glib::ustring PresetFile::get_name(int n) {
    reopen();
    return entries.at(n).name;
}

int PresetFile::get_index(const Glib::ustring& name) {
    reopen();
    for (int i = 0; i < size(); i++) {
	if (name == entries[i].name) {
	    return i;
	}
    }
    return -1;
}

JsonParser *PresetFile::create_reader(int n) {
    reopen();
    JsonParser *jp = new JsonParser(is);
    jp->set_streampos(entries.at(n).pos);
    return jp;
}

PresetTransformer::PresetTransformer(string fname, istream* is_)
    : JsonWriter(),
      filename(fname),
      tmpfile(filename + "_tmp"),
      os(tmpfile.c_str()),
      is(is_),
      jp(is_),
      header() {
    set_stream(&os);
    if (!is->fail()) {
	is->seekg(0);
	jp.next(JsonParser::begin_array);
	header.read(jp);
    }
    begin_array();
    header.write(*this);
}

PresetTransformer::~PresetTransformer() {
    // JsonParser destructor will only run JsonParser::close()
    close();
}

void PresetTransformer::close() {
    if (is_closed()) {
	return;
    }
    if (!is->fail()) {
	jp.next(JsonParser::end_array);
	jp.next(JsonParser::end_token);
    }
    end_array(true);
    JsonWriter::close();
    delete is;
    is = 0;
    os.close();
    if (!os.good()) {
	gx_print_error(_("save preset"),
		       boost::format(_("couldn't write %1%")) % tmpfile);
	return;
    }
    int rc = rename(tmpfile.c_str(), filename.c_str());
    if (rc != 0) {
	gx_print_error(_("save preset"),
		       boost::format(_("couldn't rename %1% to %2%"))
		       % tmpfile % filename);
    }
}

class ModifyPreset: public PresetTransformer {
public:
    ModifyPreset(string filename, istream* is, const Glib::ustring& presname);
    ~ModifyPreset();
    void close();
};

ModifyPreset::~ModifyPreset() {
    close();
}

ModifyPreset::ModifyPreset(string fname, istream* is, const Glib::ustring& presname)
    : PresetTransformer(fname, is) {
    if (!is->fail()) {
	while (jp.peek() != JsonParser::end_array) {
	    jp.next(JsonParser::value_string);
	    if (jp.current_value() == presname) {
		return;
	    } else {
		write(jp.current_value());
		jp.copy_object(*this);
	    }
	}
    }
}

void ModifyPreset::close() {
    if (is_closed()) {
	return;
    }
    if (!is->fail()) {
	while (jp.peek() != JsonParser::end_array) {
	    jp.next(JsonParser::value_string);
	    write(jp.current_value());
	    jp.copy_object(*this);
	}
    }
    PresetTransformer::close();
}

JsonWriter *PresetFile::create_writer(const Glib::ustring& name) {
    reopen();
    ModifyPreset *jw = new ModifyPreset(filename, is, name);
    jw->write(name);
    if (!is->fail()) {
	if (jw->jp.peek() != JsonParser::end_array) {
	    jw->jp.skip_object(); // we are replacing a setting
	}
    }
    is = 0;
    return jw;
}

PresetTransformer *PresetFile::create_transformer() {
    reopen();
    PresetTransformer *tr = new PresetTransformer(filename, is);
    is = 0;
    return tr;
}

bool PresetFile::erase(const Glib::ustring& name) {
    reopen();
    if (get_index(name) < 0) {
	return false;
    }
    ModifyPreset jw(filename, is, name);
    is = 0;
    jw.jp.skip_object();
    return true;
}

bool PresetFile::clear() {
    if (!SettingsFileHeader::make_empty_settingsfile(filename)) {
	return false;
    }
    open(filename);
    return true;
}

bool PresetFile::rename(const Glib::ustring& name, Glib::ustring newname) {
    reopen();
    if (get_index(name) < 0) {
	return false;
    }
    ModifyPreset jw(filename, is, name);
    is = 0;
    jw.write(newname);
    jw.jp.copy_object(jw);
    return true;
}

void PresetFile::append(const Glib::ustring& name) {
    //entries.push_back(name);
}

void PresetFile::insert_before(const Glib::ustring& nm, const Glib::ustring& newentry) {
    //settings.insert(std::find(settings.begin(), settings.end(), nm), newentry);
}

void PresetFile::insert_after(const Glib::ustring& nm, const Glib::ustring& newentry) {
    //std::list<Glib::ustring>::iterator i = std::find(settings.begin(), settings.end(), nm);
    //settings.insert(++i, newentry);
}

void PresetFile::reorder(const std::list<Glib::ustring>& settingslist) {
    //print "PD", namelist
    //assert len(namelist) == len(self.settings)
    //settings = settingslist;
}


/****************************************************************
 ** class PresetBanks
 */

PresetBanks::PresetBanks()
    : banklist(), filepath(), preset_dir() {
}

PresetBanks::~PresetBanks() {
    for (iterator i = begin(); i != end(); ++i) {
	delete *i;
    }
}

void PresetBanks::parse(
    const std::string& bank_path, const std::string& preset_dir_,
    const std::string& factory_dir) {
    filepath = bank_path;
    preset_dir = preset_dir_;
#ifndef OLDUSERDIR
    parse_bank_list();
#endif
    parse_factory_list(factory_dir);
}

void PresetBanks::save() {
    ofstream f(filepath.c_str());
    if (!f.good()) {
	gx_system::gx_print_error(
	    _("Presets"),
	    boost::format(_("can't create '%1%'")) % filepath);
    }
    gx_system::JsonWriter jw(&f);
    jw.begin_array(true);
    for (iterator i = begin(); i != end(); ++i) {
	int tp = i->get_type();
	if (tp == PresetFile::PRESET_FILE || tp == PresetFile::PRESET_SCRATCH) {
	    jw.begin_array();
	    jw.write(i->get_name());
	    jw.write(i->get_filename());
	    jw.write(tp);
	    jw.write(i->get_flags());
	    gx_system::SettingsFileHeader::write_major_minor_version(jw); //version FIXME
	    jw.write(0); // mtime FIXME
	    jw.end_array(true);
	}
    }
    jw.end_array(true);
    jw.close();
    f.close();
}

void PresetBanks::parse_factory_list(const std::string& path) {
    ifstream is(Glib::build_filename(path, "dirlist.js").c_str());
    if (is.fail()) {
	gx_system::gx_print_error(_("Presets"), _("factory preset list not found"));
	return;
    }
    gx_system::JsonParser jp(&is);
    jp.next(gx_system::JsonParser::begin_array);
    while (jp.peek() != gx_system::JsonParser::end_array) {
	jp.next(gx_system::JsonParser::begin_array);
	jp.next(gx_system::JsonParser::value_string);
	string name = jp.current_value();
	jp.next(gx_system::JsonParser::value_string);
	string fname = Glib::build_filename(path, jp.current_value());
	PresetFile *f = new PresetFile(name, fname, PresetFile::PRESET_FACTORY, 0, SettingsFileHeader(), 0);
	try {
	    f->open(fname);
	    add_nosave(f);
	} catch (gx_system::JsonException& e) {
	    delete f;
	    gx_system::gx_print_error(fname.c_str(), _("not found or parse error"));
	}
	jp.next(gx_system::JsonParser::end_array);
    }
    jp.next(gx_system::JsonParser::end_array);
    jp.next(gx_system::JsonParser::end_token);
    jp.close();
    is.close();
}

void PresetBanks::parse_bank_list() {
    //FIXME catch errors
    ifstream is(filepath.c_str());
    if (is.fail()) {
	gx_system::gx_print_error(
	    _("Presets"), boost::format(_("banks not found: '%1%'")) % filepath);
	return;
    }
    gx_system::JsonParser jp(&is);
    jp.next(gx_system::JsonParser::begin_array);
    while (jp.peek() != gx_system::JsonParser::end_array) {
	jp.next(gx_system::JsonParser::begin_array);
	jp.next(gx_system::JsonParser::value_string);
	Glib::ustring name = jp.current_value();
	jp.next(gx_system::JsonParser::value_string);
	string path = Glib::build_filename(preset_dir, jp.current_value());
	jp.next(gx_system::JsonParser::value_number);
	int tp = jp.current_value_int();
	jp.next(gx_system::JsonParser::value_number);
	int flags = jp.current_value_int();
	gx_system::SettingsFileHeader head;
	head.read_major_minor_version(jp);
	if (!head.is_current()) {
	    flags |= PRESET_FLAG_VERSIONDIFF;
	}
	jp.next(gx_system::JsonParser::value_number);
	time_t mtime = jp.current_value_int();
	PresetFile *f = new PresetFile(name, path, tp, flags, head, mtime);
	try {
	    add_nosave(f);
	} catch (gx_system::JsonException& e) {
	    delete f;
	    gx_system::gx_print_error(path.c_str(), _("not found or parse error"));
	}
	jp.next(gx_system::JsonParser::end_array);
    }
    jp.next(gx_system::JsonParser::end_array);
    jp.next(gx_system::JsonParser::end_token);
    jp.close();
    is.close();
}

PresetFile *PresetBanks::get_file(const Glib::ustring& bank) const {
    for (bl_type::const_iterator i = banklist.begin(); i != banklist.end(); ++i) {
	if ((*i)->get_name() == bank) {
	    return *i;
	}
    }
    return 0;
}

bool PresetBanks::rename(const Glib::ustring& oldname, const Glib::ustring& newname) {
    PresetFile *f = get_file(oldname);
    if (!f) {
	return false;
    }
    f->set_name(newname);
    save();
    return true;
}

bool PresetBanks::remove(const Glib::ustring& bank) {
    PresetFile *f = get_file(bank);
    if (!f) {
	return false;
    }
    banklist.remove(f);
    //FIXME: delete file
    delete f;
    save();
    return true;
}

void PresetBanks::reorder(const std::vector<Glib::ustring>& neworder) {
    bl_type::iterator j = banklist.begin();
    for (std::vector<Glib::ustring>::const_iterator i = neworder.begin(); i != neworder.end(); ++i) {
	assert(j != banklist.end());
	if (*i == (*j)->get_name()) {
	    ++j;
	} else {
	    for (bl_type::iterator k = j; k != banklist.end(); ++k) {
		if (*i == (*k)->get_name()) {
		    banklist.splice(j, banklist, k);
		    break;
		}
	    }
	}
    }
    save();
}


/****************************************************************
 ** class GxSettingsBase
 */

AbstractStateIO::~AbstractStateIO() {}
AbstractPresetIO::~AbstractPresetIO() {}

// seq_ may not yet be initialized, only use address!
GxSettingsBase::GxSettingsBase(gx_engine::EngineControl& seq_)
    : state_io(),
      preset_io(),
      statefile(),
      banks(),
      presetfile(),
      factory_presets(),
      current_source(state),
      current_factory(),
      current_name(),
      seq(seq_),
      selection_changed(),
      presetlist_changed() {
}

GxSettingsBase::~GxSettingsBase() {
    clear_factory();
}

void GxSettingsBase::clear_factory() {
    for (unsigned int i = 0; i < factory_presets.size(); i++) {
	delete factory_presets[i];
    }
}

void GxSettingsBase::change_preset_file(const std::string& newfile) {
    if (presetfile.get_filename() == newfile) {
	presetfile.reopen();
    } else {
	presetfile.open(newfile);
	if (current_source == preset) {
	    current_source = state;
	    current_name = "";
	    selection_changed();
	}
    }
    presetlist_changed();
}

PresetFile* GxSettingsBase::get_factory(const Glib::ustring& name) const {
    for (unsigned int i = 0; i < factory_presets.size(); i++) {
	if (name == factory_presets[i]->name) {
	    return &factory_presets[i]->setting;
	}
    }
    return 0;
}

void GxSettingsBase::loadsetting(PresetFile *p, const Glib::ustring& name) {
    try {
	if (p) {
	    JsonParser *jp = p->create_reader(name);
	    preset_io->read_preset(*jp, p->get_header());
	    seq.wait_ramp_down_finished();
	    preset_io->commit_preset();
	    delete jp;
	    gx_print_info(
		_("loaded preset"),
		boost::format(_("%1% from file %2%")) % name % p->get_filename());
	} else {
	    JsonParser *jp = statefile.create_reader();
	    state_io->read_state(*jp, statefile.get_header());
	    seq.wait_ramp_down_finished();
	    state_io->commit_state();
	    delete jp;
	    gx_print_info(
		_("loaded state"),
		boost::format(_("from file %1%")) % statefile.get_filename());
	}
	seq.update_module_lists();
    } catch(JsonException& e) {
	if (p) {
	    gx_print_error(
		_("load preset"),
		boost::format(_("error loading %1% from file %2%")) % name % p->get_filename());
	} else {
	    gx_print_warning(
		_("load state"),
		boost::format(_("error loading state from file %1%"))
		% statefile.get_filename());
	}
    }
}

void GxSettingsBase::loadstate() {
    current_source = state;
    current_factory = current_name = "";
    seq.start_ramp_down();
    loadsetting(0, current_name);
    PresetFile *p = 0;
    if (!current_factory.empty()) {
	p = get_factory(current_factory);
	if (p && p->get_index(current_name) >= 0) {
	    current_source = factory;
	} else {
	    current_factory = current_name = "";
	}
    } else if (!current_name.empty()) {
	if (presetfile.get_index(current_name) >= 0) {
	    p = &presetfile;
	    current_source = preset;
	    current_factory = "";
	}
    }
    if (p) {
	loadsetting(p, current_name);
    }
    seq.start_ramp_up();
    gx_ui::GxUI::updateAllGuis();
    seq.clear_rack_changed();
    selection_changed();
}

void GxSettingsBase::load(Source src, const Glib::ustring& name, const Glib::ustring& factoryname) {
    PresetFile *p = 0;
    switch (src) {
    case preset:
	if (presetfile.get_index(name) < 0) {
	    return;
	}
	p = &presetfile;
	current_source = src;
	current_name = name;
	current_factory = "";
	break;
    case factory:
	p = get_factory(factoryname);
	if (!p) {
	    return;
	}
	if (p->get_index(name) < 0) {
	    return;
	}
	current_source = src;
	current_name = name;
	current_factory = factoryname;
	break;
    case state:
    default:
	current_source = state;
	current_factory = current_name = "";
	break;
    }
    seq.start_ramp_down();
    loadsetting(p, name);
    seq.start_ramp_up();
    if (current_source == state) {
	// might have changed because we read all state file sections
	current_factory = current_name = "";
    }
    gx_ui::GxUI::updateAllGuis();
    seq.clear_rack_changed();
    selection_changed();
}

void GxSettingsBase::set_source_to_state() {
    current_source = state;
    current_factory = current_name = "";
    selection_changed();
}

void GxSettingsBase::save_to_state(bool preserve_preset) {
    gx_system::gx_print_info("write state",boost::format("%2% [%1%]")
			     % preserve_preset % statefile.get_filename());
    JsonWriter *jw = statefile.create_writer(&preserve_preset);
    state_io->write_state(*jw, preserve_preset);
    delete jw;
    if (!preserve_preset && current_source != state) {
	set_source_to_state();
    }
}

void GxSettingsBase::save_to_preset(const Glib::ustring& name) {
    bool newentry = (presetfile.get_index(name) < 0);
    JsonWriter *jw = 0;
    try {
	jw = presetfile.create_writer(name);
	preset_io->write_preset(*jw);
    } catch(JsonException& e) {
	gx_print_warning(
	    _("save preset"),
	    boost::format(_("parse error in %1%"))
	    % presetfile.get_filename());
    }
    delete jw;
    if (newentry) {
	presetlist_changed();
    }
    if (current_source != preset
	|| (current_source == preset && current_name != name)) {
	current_source = preset;
	current_name = name;
	current_factory = "";
	selection_changed();
    }
}

bool GxSettingsBase::rename_preset(const Glib::ustring& name, const Glib::ustring& newname) {
    bool rv = false;
    try {
	rv = presetfile.rename(name, newname);
    } catch(JsonException& e) {
	gx_print_warning(
	    _("rename preset"),
	    boost::format(_("parse error in %1%"))
	    % presetfile.get_filename());
	rv = false;
    }
    if (rv && current_source == preset && current_name == name) {
	current_name = newname;
	selection_changed();
    }
    presetlist_changed();
    return rv;
}

void GxSettingsBase::erase_preset(const Glib::ustring& name) {
    try {
	presetfile.erase(name);
    } catch(JsonException& e) {
	gx_print_warning(
	    _("delete preset"),
	    boost::format(_("parse error in %1%"))
	    % presetfile.get_filename());
    }
    presetlist_changed();
}

bool GxSettingsBase::clear_preset() {
    bool rv = presetfile.clear();
    presetlist_changed();
    return rv;
}

void GxSettingsBase::convert_presetfile() {
    PresetTransformer *jw = 0;
    try {
	jw = presetfile.create_transformer();
	while (jw->jp.peek() != JsonParser::end_array) {
	    jw->jp.next(JsonParser::value_string);
	    jw->write(jw->jp.current_value());
	    preset_io->copy_preset(jw->jp, jw->header, *jw);
	}
    } catch(JsonException& e) {
	gx_print_warning(
	    _("convert presetfile"),
	    boost::format(_("parse error in %1%"))
	    % presetfile.get_filename());
    }
    delete jw;
    try {
	JsonParser *jp = statefile.create_reader();
	state_io->read_state(*jp, statefile.get_header());
	state_io->commit_state();
	delete jp;
    } catch(JsonException& e) {
	// state file error will be reported elsewhere
    }
}

void GxSettingsBase::fill_factory_names(vector<Glib::ustring>& l) const
{
    for (unsigned int i = 0; i < factory_presets.size(); i++) {
	l.push_back(factory_presets[i]->name);
    }
}

void GxSettingsBase::fill_factory_preset_names(const Glib::ustring& fact, vector<Glib::ustring>& l) const
{
    PresetFile* p = get_factory(fact);
    assert(p);
    if (p) {
	p->fill_names(l);
    }
}

} /* end of gx_system namespace */