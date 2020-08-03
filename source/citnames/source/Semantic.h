/*  Copyright (C) 2012-2020 by László Nagy
    This file is part of Bear.

    Bear is a tool to generate compilation database for clang tooling.

    Bear is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Bear is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "Configuration.h"
#include "Tool.h"
#include "CompilationDatabase.h"
#include "libresult/Result.h"
#include "libreport/Report.h"

namespace cs {

    // Represents an expert system which can recognize compilation entries from
    // command executions. It covers multiple tools and consider omit results
    // based on configuration.
    class Semantic {
    public:
        static rust::Result<Semantic> from(cfg::Value cfg);

        [[nodiscard]]
        output::Entries transform(const report::Report& report) const;

        [[nodiscard]]
        rust::Result<output::Entries> recognize(const report::Command& command) const;

        [[nodiscard]]
        bool filter(const output::Entry&) const;

    public:
        using ToolPtr = std::shared_ptr<Tool>;
        using Tools = std::list<ToolPtr>;

        Semantic() = delete;
        ~Semantic() noexcept = default;

        Semantic(cfg::Value&&, Tools &&) noexcept;

    private:
        cfg::Value config_;
        Tools tools_;
    };
}