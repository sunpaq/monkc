package _Self.buildTypes

import jetbrains.buildServer.configs.kotlin.v2019_2.*
import jetbrains.buildServer.configs.kotlin.v2019_2.buildSteps.script
import jetbrains.buildServer.configs.kotlin.v2019_2.triggers.vcs

object Build : BuildType({
    name = "Build"

    artifactRules = "example/_build/archive/lib/exp"

    vcs {
        root(HttpsGithubComSunpaqMonkcGitRefsHeadsMaster)
    }

    steps {
        script {
            scriptContent = "ruby build.rb all"
        }
    }

    triggers {
        vcs {
        }
    }
})
