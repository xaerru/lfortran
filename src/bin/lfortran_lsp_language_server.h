#pragma once

#include <memory>
#include <shared_mutex>
#include <string>
#include <unordered_map>

#include <libasr/asr.h>
#include <libasr/diagnostics.h>
#include <libasr/utils.h>

#include <server/base_lsp_language_server.h>
#include <server/logger.h>
#include <server/lsp_specification.h>

#include <bin/lfortran_accessor.h>
#include <bin/lfortran_lsp_config.h>

namespace LCompilers::LanguageServerProtocol {
    namespace ls = LCompilers::LLanguageServer;
    namespace lsl = LCompilers::LLanguageServer::Logging;
    namespace lsc = LCompilers::LanguageServerProtocol::Config;

    class LFortranLspLanguageServer : public BaseLspLanguageServer {
    public:
        LFortranLspLanguageServer(
            ls::MessageQueue &incomingMessages,
            ls::MessageQueue &outgoingMessages,
            std::size_t numRequestThreads,
            std::size_t numWorkerThreads,
            lsl::Logger &logger,
            const std::string &configSection,
            std::shared_ptr<lsc::LspConfig> workspaceConfig
        );
    protected:

        auto invalidateConfigCache() -> void override;

        // ================= //
        // Incoming Requests //
        // ================= //

        auto receiveInitialize(
            InitializeParams &params
        ) -> InitializeResult override;

        auto receiveTextDocument_definition(
            DefinitionParams &params
        ) -> TextDocument_DefinitionResult override;

        // ====================== //
        // Incoming Notifications //
        // ====================== //

        auto receiveWorkspace_didDeleteFiles(
            DeleteFilesParams &params
        ) -> void override;

        auto receiveWorkspace_didChangeConfiguration(
            DidChangeConfigurationParams &params
        ) -> void override;

        auto receiveTextDocument_didOpen(
            DidOpenTextDocumentParams &params
        ) -> void override;

        auto receiveTextDocument_didChange(
            DidChangeTextDocumentParams &params
        ) -> void override;

        auto receiveWorkspace_didChangeWatchedFiles(
            DidChangeWatchedFilesParams &params
        ) -> void override;

    private:
        const std::string source = "lfortran";
        ls::LFortranAccessor lfortran;
        std::unordered_map<
            DocumentUri,
            std::shared_ptr<CompilerOptions>
        > optionsByUri;
        std::shared_mutex optionMutex;

        std::atomic_bool clientSupportsGotoDefinition = false;
        std::atomic_bool clientSupportsGotoDefinitionLinks = false;

        auto validate(std::shared_ptr<LspTextDocument> document) -> void;
        auto getCompilerOptions(
            const LspTextDocument &document
        ) -> const std::shared_ptr<CompilerOptions>;

        auto diagnosticLevelToLspSeverity(
            diag::Level level
        ) const -> DiagnosticSeverity;

        auto asrSymbolTypeToLspSymbolKind(
            ASR::symbolType symbol_type
        ) const -> SymbolKind;

        auto getLFortranConfig(
            const DocumentUri &uri
        ) -> const std::shared_ptr<lsc::LFortranLspConfig>;

        auto resolve(
            const std::string &filename,
            const CompilerOptions &compilerOptions
        ) -> fs::path;
    };

} // namespace LCompilers::LanguageServerProtocol
